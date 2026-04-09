// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Renewa.h"

void ARenewa::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Renewa Interaction"));
}

void ARenewa::OnStageStart(EAnomalyType AnomalyType)
{
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_RenewaQuiz:
			EnableCharacterMesh();
			break;
		default:
			DisableCharacterMesh();
			break;
	}
}
