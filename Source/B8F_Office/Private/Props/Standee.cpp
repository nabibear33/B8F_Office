// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Standee.h"

AStandee::AStandee()
{
	StandeeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StandeeMesh"));
	StandeeMesh->SetupAttachment(RootComponent);
}

void AStandee::BeginPlay()
{
	Super::BeginPlay();
}

void AStandee::OnStageStart(EAnomalyType AnomalyType)
{
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_ChangeStandee:
			SetRanMesh();
			break;

		default:
			SetNormal();
			break;

	}
}

void AStandee::SetRanMesh()
{
	if (StandeeMesh && RanMesh)
	{
		StandeeMesh->SetStaticMesh(RanMesh);
	}
}

void AStandee::SetNormal()
{
	if (StandeeMesh && ButterMesh)
	{
		StandeeMesh->SetStaticMesh(ButterMesh);
	}
}
