
#include "GameManager/StageManager.h"
#include "GameLogics/NotKommyTriggerArea.h"
#include "Components/InteractComponent.h"
#include "Characters/MainCharacter.h"
#include "Characters/NotKommy.h"

AStageManager::AStageManager()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void AStageManager::BeginPlay()
{
	Super::BeginPlay();	
}

void AStageManager::ResetStage()
{
	float RollIfAnomaly = FMath::FRandRange(0.0f, 1.0f);
	if ((RollIfAnomaly < AnomalyProbability) || bTestAnomaly)
	{
		StageState = EStageState::ESS_Anomaly;
		AnomalyStatus = EAnomalyStatus::EAS_SeenButNotFound;
		int32 RollAnomalyType = FMath::RandRange(1, GetAnomalyTotalCount());
		AnomalyType = bTestAnomaly ? TestAnomalyType : static_cast<EAnomalyType>(RollAnomalyType);


		OnStageStart.Broadcast(AnomalyType);
		UE_LOG(LogTemp, Warning, TEXT("Reset Anomaly"));
	}
	else
	{
		SetNormalStage();
	}

	FInteractableList* Found = AnomalyInteractableMap.Find(AnomalyType);
	if (Found)
	{
		for (AActor* Actor : Found->Interactables)
		{
			CurrentStageInteractableList.Interactables.Add(Actor);

			IInteractable* Interactable = Cast<IInteractable>(Actor);
			if (Interactable)
			{
				Interactable->GetInteractComponent()->OnInteractableEntered.RemoveDynamic(Player, &AMainCharacter::OnInteractableEntered);
				Interactable->GetInteractComponent()->OnInteractableLeft.RemoveDynamic(Player, &AMainCharacter::OnInteractableLeft);
				Interactable->GetInteractComponent()->OnInteractableEntered.AddDynamic(Player, &AMainCharacter::OnInteractableEntered);
				Interactable->GetInteractComponent()->OnInteractableLeft.AddDynamic(Player, &AMainCharacter::OnInteractableLeft);
			}
		}
	}
}

void AStageManager::SetNormalStage()
{
	StageState = EStageState::ESS_Normal;
	AnomalyType = EAnomalyType::EAT_Normal;
	AnomalyStatus = EAnomalyStatus::EAS_Found;

	OnStageStart.Broadcast(EAnomalyType::EAT_Normal);
	UE_LOG(LogTemp, Warning, TEXT("Initialize Stage"));
}