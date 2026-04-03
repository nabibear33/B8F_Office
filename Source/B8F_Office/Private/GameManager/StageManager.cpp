
#include "GameManager/StageManager.h"
#include "GameLogics/NotKommyTriggerArea.h"
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
}

void AStageManager::SetNormalStage()
{
	StageState = EStageState::ESS_Normal;
	AnomalyType = EAnomalyType::EAT_Normal;
	AnomalyStatus = EAnomalyStatus::EAS_Found;

	OnStageStart.Broadcast(EAnomalyType::EAT_Normal);
	UE_LOG(LogTemp, Warning, TEXT("Initialize Stage"));
}