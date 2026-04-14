// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogueComponent.h"
#include "HUD/MainHUD.h"
#include "DataTables/DialogueRow.h"

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

void UDialogueComponent::StartDialogue()
{
    UE_LOG(LogTemp, Warning, TEXT("StartDialogue"));
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
        if (HUD)
        {
            HUD->ShowDialogueWidget(this);
        }
    }

    AdvanceDialogue(CurrentRowID);
}

void UDialogueComponent::AdvanceDialogue(FName ChoiceRowID)
{
    FName TargetRow = ChoiceRowID.IsNone() ? CurrentRowID : ChoiceRowID;
    UE_LOG(LogTemp, Warning, TEXT("ChoiceRowID: %s"), *ChoiceRowID.ToString());
    UE_LOG(LogTemp, Warning, TEXT("TargetRow: %s"), *TargetRow.ToString());

    if(!DialogueDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("No DataTable linked."));
        return;
    }
    FDialogueRow* Row = DialogueDataTable->FindRow<FDialogueRow>(TargetRow, TEXT(""));

    if (!Row || Row->NextRowID.IsNone() && Row->Choices.IsEmpty())
    {
        EndDialogue();
        return;
    }

    CurrentRowID = Row->NextRowID;
    OnDialogueUpdated.Broadcast(*Row);
    AdvanceDialogue(CurrentRowID);
}

void UDialogueComponent::EndDialogue()
{
    UE_LOG(LogTemp, Warning, TEXT("EndDialogue"));
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD()))
    {
        HUD->HideDialogueWidget();
    }

}

