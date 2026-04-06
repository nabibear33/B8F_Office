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

void UDialogueComponent::StartDialogue(APlayerController* Instigator)
{
    AMainHUD* HUD = Cast<AMainHUD>(Instigator->GetHUD());
    if (HUD)
    {
        HUD->ShowDialogueWidget(this);
    }

    Instigator->SetInputMode(FInputModeUIOnly());
    Instigator->SetShowMouseCursor(true);

    AdvanceDialogue();
}

void UDialogueComponent::AdvanceDialogue(FName ChoiceRowID)
{
    FName TargetRow = ChoiceRowID.IsNone() ? CurrentRowID : ChoiceRowID;
    FDialogueRow* Row = DialogueTable->FindRow<FDialogueRow>(TargetRow, TEXT(""));

    if (!Row || Row->NextRowID.IsNone() && Row->Choices.IsEmpty())
    {
        EndDialogue();
        return;
    }

    CurrentRowID = Row->NextRowID;
    OnDialogueUpdated.Broadcast(*Row);
}

void UDialogueComponent::EndDialogue()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD()))
    {
        HUD->HideDialogueWidget();
    }

    PC->SetInputMode(FInputModeGameOnly());
    PC->SetShowMouseCursor(false);
}

