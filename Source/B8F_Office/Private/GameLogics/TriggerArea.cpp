

#include "GameLogics/TriggerArea.h"
#include "GameLogics/Types.h"
#include "GameManager/StageManager.h"
#include "Kismet/GameplayStatics.h"

ATriggerArea::ATriggerArea()
{
}

void ATriggerArea::BeginPlay()
{
	Super::BeginPlay();

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &ATriggerArea::OnStageStart);
	}

	SetNormal();
}

void ATriggerArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATriggerArea::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType == LinkedAnomalyType)
	{
		EnableArea();
	}
	else
	{
		SetNormal();
	}
}

void ATriggerArea::SetNormal()
{
	DisableArea();
}
