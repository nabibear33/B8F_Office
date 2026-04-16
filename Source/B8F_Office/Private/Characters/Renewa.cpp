// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Renewa.h"
#include "Controllers/MainCharacterController.h"


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
		PC->StartDialogue(DialogueDataTable, FName(TEXT("Test_001")));
	}
}

void ARenewa::OnStageStart(EAnomalyType AnomalyType)
{
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_RenewaQuiz:
			EnableCharacterMesh();
			break;
		default:
			DisableCharacterMesh();
			break;
	}
}
