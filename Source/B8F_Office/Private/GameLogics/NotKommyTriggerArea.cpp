

#include "GameLogics/NotKommyTriggerArea.h"
#include "Characters/NotKommy.h"
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
	OnAreaTriggered.RemoveDynamic(LinkedKommy, &ANotKommy::OnNotKommyTriggerAreaTriggered);

	switch(AnomalyType)
	{
		case EAnomalyType::EAT_NotKommyChase:
			OnAreaTriggered.AddDynamic(LinkedKommy, &ANotKommy::OnNotKommyTriggerAreaTriggered);
			EnableArea();
			break;

		default:
			break;

	}
}

void ANotKommyTriggerArea::SetNormal()
{
	DisableArea();
}
