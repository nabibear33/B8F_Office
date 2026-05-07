// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Renewa.h"
#include "Components/InteractComponent.h"
#include "Controllers/MainCharacterController.h"
#include "Components/DialogueComponent.h"


void ARenewa::BeginPlay()
{
	Super::BeginPlay();

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		// bind death scene delegate here
		UE_LOG(LogTemp, Warning, TEXT("Binding KillPlayer to OnDeathSceneChoiceSelected delegate"));
		PC->GetDialogueComponent()->OnDeathSceneChoiceSelected.RemoveDynamic(this, &ARenewa::KillPlayer);
		PC->GetDialogueComponent()->OnDeathSceneChoiceSelected.AddDynamic(this, &ARenewa::KillPlayer);
	}
}

void ARenewa::Interact_Implementation()
{
	if (!GetIsInteractable()) return;
	UE_LOG(LogTemp, Warning, TEXT("Renewa Interaction"));

	
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		if (!DialogueDataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("No DataTable linked."));
			return;
		}

		InteractComponent->SetInteractDisabled();
		
		if(bHasTalkedToPlayerOnCurrentStage)
		{
			PC->StartDialogue(this, DialogueDataTable, FName(TEXT("Renewa_AlreadyTalked")));
		}
		else
		{
			PC->StartDialogue(this, DialogueDataTable, FName(TEXT("Renewa_001")));
			bHasTalkedToPlayerOnCurrentStage = true;
		}
	}

}

void ARenewa::OnStageStart(EAnomalyType AnomalyType)
{
	bHasTalkedToPlayerOnCurrentStage = false;
	
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_RenewaQuiz:
			InteractComponent->SetInteractEnabled();
			EnableCharacterMesh();
			break;
		default:
			InteractComponent->SetInteractDisabled();
			DisableCharacterMesh();
			break;
	}
}

void ARenewa::KillPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("KillPlayer"));
	InteractComponent->SetInteractDisabled();
	OnPlayCutscene.Broadcast(ECutsceneName::ECN_RenewaQuiz);
}
