// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Seat.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Controllers/MainCharacterController.h"
#include "Characters/MainCharacter.h"

ASeat::ASeat()
{
	SitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SitPoint"));
	SitPoint->SetupAttachment(RootComponent);

	SeatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SeatMesh"));
	SeatMesh->SetupAttachment(RootComponent);
}

void ASeat::DisableCollision()
{
	SeatMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASeat::Interact_Implementation()
{
	ABaseProp::Interact_Implementation();

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMainCharacter* Player = Cast<AMainCharacter>(PC->GetPawn());
		if (Player)
		{
			switch (Player->GetCharacterState())
			{
				case ECharacterState::ECS_Sit:
					Player->Stand();
					break;
				case ECharacterState::ECS_Idle:
					Player->Sit(this);
				default:
					break;

			}
		}
	}
}


