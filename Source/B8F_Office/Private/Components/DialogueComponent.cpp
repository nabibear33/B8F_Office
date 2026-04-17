// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogueComponent.h"
#include "HUD/MainHUD.h"
#include "DataTables/DialogueRow.h"
#include "Controllers/MainCharacterController.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDialogueComponent::StartDialogue(UDataTable* DialogueRows, FName ID)
{
	SetDialogueDataTable(DialogueRows);
	SetCurrentRowID(ID);
    UE_LOG(LogTemp, Warning, TEXT("StartDialogue"));
    AdvanceDialogue();
}

void UDialogueComponent::AdvanceDialogue(FName ChoiceRowID)
{
    // For Row that requires choice
    if (bIsWaitingForChoice) return;

    FName TargetRow = ChoiceRowID.IsNone() ? CurrentRowID : ChoiceRowID;

    FDialogueRow* Row = DialogueDataTable->FindRow<FDialogueRow>(TargetRow, TEXT(""));

    if (Row)
    {
		CurrentRow = *Row;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Row. End Dialogue."));
        CurrentRow.Reset();
        EndDialogue();
        return;
    }

    OnDialogueUpdated.Broadcast(*Row);

    if (IsLastRow(Row))
    {   
		SetCurrentRowID(NAME_None);
        return;
    }

    if (IsRowRequiresChoice(Row))
    {
		CurrentChoiceIdx = 0;
		bIsWaitingForChoice = true;
        return;
    }

    // update current row id in advance in normal case
    SetCurrentRowID(Row->NextRowID);
}

bool UDialogueComponent::IsRowRequiresChoice(FDialogueRow* Row)
{
    return Row->NextRowID.IsNone() && !Row->Choices.IsEmpty();
}

bool UDialogueComponent::IsLastRow(FDialogueRow* Row)
{
    return Row->NextRowID.IsNone() && Row->Choices.IsEmpty();
}

void UDialogueComponent::EndDialogue()
{
    UE_LOG(LogTemp, Warning, TEXT("EndDialogue"));
    AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
    if (PC)
    {
        PC->EndDialogue();
    }
    SetDialogueDataTable(nullptr);
    SetCurrentRowID(NAME_None);
    CurrentRow.Reset();
}

void UDialogueComponent::NavigateCurrentChoiceIdx(float Value)
{
	if (CurrentRow.IsSet() && !IsCurrentRowHasChoices()) return;

    int32 Delta = Value > 0.f ? -1 : 1;
	CurrentChoiceIdx = FMath::Clamp(CurrentChoiceIdx + Delta, 0, GetCurrentChoiceNum() - 1);
}

void UDialogueComponent::OnSelectCurrentChoice()
{
    if (!CurrentRow.IsSet() || !IsCurrentRowHasChoices()) return;
	UE_LOG(LogTemp, Warning, TEXT("Select Choice: %d"), CurrentChoiceIdx);
    FName SelectedChoiceRowID = CurrentRow->Choices[CurrentChoiceIdx].NextRowID;
    CurrentChoiceIdx = -1;
	bIsWaitingForChoice = false;
    AdvanceDialogue(SelectedChoiceRowID);
}



