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
	MeshComponent->SetVisibility(false);
}

void AAppearOnAnomalyProp::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType == CorrespondingAnomalyType)
	{
		MeshComponent->SetVisibility(true);
	}
}
