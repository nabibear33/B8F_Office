
#include "Characters/NotKommy.h"
#include "Characters/MainCharacter.h"
#include "AIController.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameLogics/TriggerArea.h"
#include "Components/CapsuleComponent.h"

ANotKommy::ANotKommy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANotKommy::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<AAIController>(GetController());
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANotKommy::OnBeginOverlap);
	InitialLocation = GetActorLocation();
	
	SetNormal();
}

void ANotKommy::SetNormal()
{
	Super::SetNormal();

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

void ANotKommy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("[NotKommy] Overlap! OtherActor: %s | OtherComp: %s"),
		OtherActor ? *OtherActor->GetName() : TEXT("NULL"),
		OtherComp ? *OtherComp->GetName() : TEXT("NULL"));
	if (!(OtherActor->IsA<AMainCharacter>() && OtherComp->IsA<UCapsuleComponent>())) return;

	OnPlayDeathScene.Broadcast(EDeathSceneType::EDS_NotKommy);
}

void ANotKommy::OnAreaTriggered(AActor* TriggeringArea, AActor* OtherActor)
{
	EnableCharacterMesh();

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		ChasePlayer(MainCharacter);
	}
}

void ANotKommy::OnStageStart(EAnomalyType AnomalyType)
{

	switch (AnomalyType)
	{
		case EAnomalyType::EAT_NotKommyChase:
			LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ANotKommy::OnAreaTriggered);
			LinkedArea->OnAreaTriggered.AddDynamic(this, &ANotKommy::OnAreaTriggered);
			// Actual action will begin when player enters the trigger area
			SetNormal();
			break;

		default:
			SetNormal();
			break;
	}
}