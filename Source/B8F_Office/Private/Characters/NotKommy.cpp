
#include "Characters/NotKommy.h"
#include "Characters/MainCharacter.h"
#include "AIController.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/CapsuleComponent.h"

ANotKommy::ANotKommy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANotKommy::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<AAIController>(GetController());
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANotKommy::OnOverlapBegin);
	InitialLocation = GetActorLocation();
	
	SetNormal();
}

void ANotKommy::SetNormal()
{
	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetActorLocation(InitialLocation);
}

void ANotKommy::ChasePlayer(AActor* Player)
{
	CharacterState = ECharacterState::ECS_Chasing;
	Controller->MoveToActor(Player);
}

void ANotKommy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ANotKommy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnPlayDeathScene.Broadcast(EDeathSceneType::EDS_NotKommy);
}

void ANotKommy::OnNotKommyTriggerAreaTriggered(AActor* TriggeringArea, AActor* OtherActor)
{
	GetMesh()->SetVisibility(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChasePlayer(OtherActor);
}

void ANotKommy::OnStageStart(EAnomalyType AnomalyType)
{

	switch (AnomalyType)
	{
		case EAnomalyType::EAT_NotKommyChase:
			// Actual action will begin when player enters the trigger area
			SetNormal();
			break;

		default:
			SetNormal();
			break;
	}
}