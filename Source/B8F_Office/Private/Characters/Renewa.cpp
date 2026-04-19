// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Renewa.h"
#include "Components/InteractComponent.h"
#include "Controllers/MainCharacterController.h"


void ARenewa::Interact_Implementation()
{
	if (bHasEverInteracted) return;
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
		// Once Dialogue Starts, disable interaction until next stage
		InteractComponent->SetInteractDisabled();
		
		bHasEverInteracted = true;
		PC->StartDialogue(DialogueDataTable, FName(TEXT("Test_001")));
	}

}

void ARenewa::OnStageStart(EAnomalyType AnomalyType)
{
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_RenewaQuiz:
			InteractComponent->SetInteractEnabled();
			EnableCharacterMesh();
			break;
		default:
			DisableCharacterMesh();
			break;
	}
}
