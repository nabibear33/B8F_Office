

#include "GameLogics/NotKommyTriggerArea.h"
#include "GameLogics/Types.h"

ANotKommyTriggerArea::ANotKommyTriggerArea()
{
}

void ANotKommyTriggerArea::BeginPlay()
{
	Super::BeginPlay();

	SetNormal();
}

void ANotKommyTriggerArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DisableArea();

	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ANotKommyTriggerArea::OnStageStart(EAnomalyType AnomalyType)
{
	if (AnomalyType == EAnomalyType::EAT_NotKommyChase)
	{
		EnableArea();
	}
}

void ANotKommyTriggerArea::SetNormal()
{
	DisableArea();
}
