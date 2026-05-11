// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/AppearOnAnomalyProp.h"
#include "Components/StaticMeshComponent.h"

AAppearOnAnomalyProp::AAppearOnAnomalyProp()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AAppearOnAnomalyProp::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetStaticMesh(MeshToAppear);
	
}

void AAppearOnAnomalyProp::OnStageStart(EAnomalyType AnomalyType)
{
	if(ActivatingAnomalyList.Contains(AnomalyType))
	{
		MeshComponent->SetVisibility(true);
	}
	else
	{
		SetNormal();
	}
}

void AAppearOnAnomalyProp::SetNormal()
{
	MeshComponent->SetVisibility(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
