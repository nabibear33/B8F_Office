// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Miro.h"
#include "Components/CapsuleComponent.h"

void AMiro::BeginPlay()
{
	Super::BeginPlay();
}

void AMiro::OnStageStart(EAnomalyType AnomalyType)
{
	if (AnomalyType == EAnomalyType::EAT_MiroAppeared)
	{
		EnableCharacterMesh();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetOwner(GetWorld()->GetFirstPlayerController()->GetPawn());
		GetMesh()->SetOwnerNoSee(true);
	}
	else
	{
		DisableCharacterMesh();
	}
}
