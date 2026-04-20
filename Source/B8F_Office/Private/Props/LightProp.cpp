// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/LightProp.h"
#include "Components/RectLightComponent.h"
#include "GameLogics/TriggerArea.h"


ALightProp::ALightProp()
{
	RectLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComponent"));
	RectLightComponent->SetupAttachment(RootComponent);
}

void ALightProp::AnomalyLightOff(AActor* TriggeringActor, AActor* TriggeredCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("AnomalyLightOff called on %s by TriggeringActor: %s, TriggeredCharacter: %s"),
		*GetActorLabel(),
		*TriggeringActor->GetActorLabel(),
		*TriggeredCharacter->GetActorLabel());
	RectLightComponent->SetVisibility(false);
	// RectLightComponent->SetIntensity(AnomalyLightIntensity);
	if (LinkedLightProp)
	{	
		GetWorld()->GetTimerManager().SetTimer(
			LightOffTimerHandle,
			[this, TriggeringActor, TriggeredCharacter]()
				{
					LinkedLightProp->AnomalyLightOff(TriggeringActor, TriggeredCharacter);
				},
			0.4f,
			false
		);
	}
}


void ALightProp::BeginPlay()
{
	Super::BeginPlay();
}

void ALightProp::OnStageStart(EAnomalyType AnomalyType)
{
	if (AnomalyType == CorrespondingAnomalyType)
	{
		if (LinkedArea)
		{
			LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ALightProp::AnomalyLightOff);
			LinkedArea->OnAreaTriggered.AddDynamic(this, &ALightProp::AnomalyLightOff);
		}
	}
	else
	{
		SetNormal();
	}
}

void ALightProp::SetNormal()
{
	RectLightComponent->SetVisibility(true);
	// RectLightComponent->SetIntensity(3000.f);
	RectLightComponent->SetLightColor(FLinearColor::White);
	if (LinkedArea)
	{
		LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ALightProp::AnomalyLightOff);
	}
}
