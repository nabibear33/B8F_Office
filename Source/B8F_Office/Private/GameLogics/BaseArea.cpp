

#include "GameLogics/BaseArea.h"
#include "Components/BoxComponent.h"
#include "GameManager/StageManager.h"
#include "Kismet/GameplayStatics.h"

ABaseArea::ABaseArea()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);
}

void ABaseArea::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseArea::OnOverlapBegin);

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &ABaseArea::OnStageStart);
	}
}

void ABaseArea::EnableArea()
{
	bIsEnabled = true;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABaseArea::DisableArea()
{
	bIsEnabled = false;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseArea::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DisableArea();

	OnAreaTriggered.Broadcast(OverlappedComp->GetOwner(), OtherActor);
}

void ABaseArea::OnStageStart(EAnomalyType AnomalyType)
{
}

void ABaseArea::SetNormal()
{
}