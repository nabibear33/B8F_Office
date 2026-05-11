// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/LightProp.h"
#include "Components/LightComponent.h"
#include "GameLogics/TriggerArea.h"
#include "GameInstances/EventBusSubsystem.h"


ALightProp::ALightProp()
{
}

void ALightProp::AnomalyLightOff(AActor* TriggeringActor, AActor* TriggeredCharacter)
{
	LightComponent->SetVisibility(false);
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

void ALightProp::OnLightColorChanged(FLinearColor Color)
{
	LightComponent->SetLightColor(Color);
}


void ALightProp::BeginPlay()
{
	Super::BeginPlay();

	if (LightComponentClass)
	{
		LightComponent = NewObject<ULightComponent>(this, LightComponentClass);
		LightComponent->SetupAttachment(RootComponent);
		LightComponent->RegisterComponent();
	}
}

void ALightProp::OnStageStart(EAnomalyType AnomalyType)
{
	if (AnomalyType == EAnomalyType::EAT_LightOff)
	{
		if (LinkedArea)
		{
			LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ALightProp::AnomalyLightOff);
			LinkedArea->OnAreaTriggered.AddDynamic(this, &ALightProp::AnomalyLightOff);
		}
	}
	else if (AnomalyType == EAnomalyType::EAT_RedLight)
	{
		UEventBusSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEventBusSubsystem>();
		if (Subsystem)
		{
			Subsystem->OnLightColorUpdated.RemoveDynamic(this, &ALightProp::OnLightColorChanged);
			Subsystem->OnLightColorUpdated.AddDynamic(this, &ALightProp::OnLightColorChanged);
		}
		
	}
	else
	{
		SetNormal();
	}
}

void ALightProp::SetNormal()
{
	LightComponent->SetVisibility(true);
	LightComponent->SetLightColor(FLinearColor::White);
}
