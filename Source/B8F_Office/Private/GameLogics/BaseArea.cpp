

#include "GameLogics/BaseArea.h"
#include "Components/BoxComponent.h"
#include "GameManager/StageManager.h"
#include "GameLogics/TriggerArea.h"
#include "Characters/MainCharacter.h"
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

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseArea::OnBeginOverlap);
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

void ABaseArea::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (!MainCharacter) return;

	UE_LOG(LogTemp, Warning, TEXT("Area Triggered : %s"), *OverlappedComp->GetOwner()->GetActorLabel());

	DisableArea();

	OnAreaTriggered.Broadcast(OverlappedComp->GetOwner(), OtherActor);
}