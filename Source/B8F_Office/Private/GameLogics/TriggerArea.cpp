

#include "GameLogics/TriggerArea.h"
#include "GameLogics/Types.h"

ATriggerArea::ATriggerArea()
{
}

void ATriggerArea::BeginPlay()
{
	Super::BeginPlay();

	SetNormal();
}

void ATriggerArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DisableArea();

	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATriggerArea::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType != LinkedAnomalyType)
	{
		SetNormal();
		return;
	}
	else
	{
		EnableArea();
	}
}

void ATriggerArea::SetNormal()
{
	DisableArea();
}
