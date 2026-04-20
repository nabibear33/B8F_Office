// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/MeshChangeableProp.h"

AMeshChangeableProp::AMeshChangeableProp()
{
	ChangeableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeableMeshComponent"));
	ChangeableMeshComponent->SetupAttachment(RootComponent);
}

void AMeshChangeableProp::BeginPlay()
{
	Super::BeginPlay();
}

void AMeshChangeableProp::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType == CorrespondingAnomalyType)
	{
		SetAnomalyMesh();
	}
	else
	{
		SetNormal();
	}
}

void AMeshChangeableProp::SetAnomalyMesh()
{
	if (ChangeableMeshComponent && AnomalyMesh)
	{
		ChangeableMeshComponent->SetStaticMesh(AnomalyMesh);
	}
}

void AMeshChangeableProp::SetNormal()
{
	if (ChangeableMeshComponent && NormalMesh)
	{
		ChangeableMeshComponent->SetStaticMesh(NormalMesh);
	}
}
