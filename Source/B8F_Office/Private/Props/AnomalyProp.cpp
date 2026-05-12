// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/AnomalyProp.h"
#include "Components/InteractComponent.h"
#include "GameManager/StageManager.h"
#include "Kismet/GameplayStatics.h"

void AAnomalyProp::OnStageStart(EAnomalyType AnomalyType)
{
}

void AAnomalyProp::SetNormal()
{
	InteractComponent->SetInteractDisabled();
}

void AAnomalyProp::BeginPlay()
{
	Super::BeginPlay();

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &AAnomalyProp::OnStageStart);
	}

	InteractComponent->SetInteractDisabled();
}
