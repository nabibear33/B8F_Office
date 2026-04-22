// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogueComponent.h"
#include "HUD/MainHUD.h"
#include "DataTables/DialogueRow.h"
#include "Controllers/MainCharacterController.h"
#include "Characters/InteractableCharacter.h"
#include "Helper/DialogueSpeakerMappingHelper.h"
#include "Kismet/GameplayStatics.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UDialogueComponent::ResetDialogueComponent()
{
	//DialogueDataTable = nullptr;
 //   CurrentRowID = NAME_None;
	//CurrentRow.Reset();
	//CurrentChoiceIdx = -1;
	//bIsWaitingForChoice = false;
 //   bDeathSceneChoiceTriggered = false;
}

void UDialogueComponent::Initialize()
{
    DialogueSpeakerMappingHelper = Cast<ADialogueSpeakerMappingHelper>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueSpeakerMappingHelper::StaticClass()));

    if (!DialogueSpeakerMappingHelper)
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueActorRegistry not found in level"));
    }
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

        // Play Anim Montage if it is valid
        if (CurrentRow->AnimMontage)
        {
            AActor* Found = DialogueSpeakerMappingHelper->GetActorFromName(CurrentRow->SpeakerID);
            if (Found)
            {
                ACharacter* Speaker = Cast<ACharacter>(Found);
                if (Speaker)
                {
                
                    UE_LOG(LogTemp, Warning, TEXT("Play Animation Montage."));
                    Speaker->PlayAnimMontage(CurrentRow->AnimMontage);
                }
            }
        }
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
        LastRowName = TargetRow;
		SetCurrentRowID(NAME_None);
        return;
    }

    if (IsRowRequiresChoice(Row))
    {
		CurrentChoiceIdx = 0;
		bIsWaitingForChoice = true;
        OnCurrentHighlightedChoiceUpdated.Broadcast(CurrentChoiceIdx);
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
    OnDialogueEnded.Broadcast(LastRowName);

    SetDialogueDataTable(nullptr);
    LastRowName = NAME_None;
    SetCurrentRowID(NAME_None);
    CurrentRow.Reset();


    if (bDeathSceneChoiceTriggered)
    {
        OnDeathSceneChoiceSelected.Broadcast();
        bDeathSceneChoiceTriggered = false;
	}
}

void UDialogueComponent::NavigateCurrentChoiceIdx(float Value)
{
	if (CurrentRow.IsSet() && !IsCurrentRowHasChoices()) return;

    int32 Delta = Value > 0.f ? -1 : 1;
	CurrentChoiceIdx = FMath::Clamp(CurrentChoiceIdx + Delta, 0, GetCurrentChoiceNum() - 1);

	OnCurrentHighlightedChoiceUpdated.Broadcast(CurrentChoiceIdx);
}

void UDialogueComponent::OnSelectCurrentChoice()
{
    if (!CurrentRow.IsSet() || !IsCurrentRowHasChoices()) return;
	UE_LOG(LogTemp, Warning, TEXT("Select Choice: %d"), CurrentChoiceIdx);
    FName SelectedChoiceRowID = CurrentRow->Choices[CurrentChoiceIdx].NextRowID;
    
    if(CurrentRow->Choices[CurrentChoiceIdx].bTriggersDeathScene)
    {
        bDeathSceneChoiceTriggered = true;
	}

    CurrentChoiceIdx = -1;
	bIsWaitingForChoice = false;
    AdvanceDialogue(SelectedChoiceRowID);
}



