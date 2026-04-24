// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/InteractableCharacter.h"
#include "Miro.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMiro : public AInteractableCharacter
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;
	virtual void OnStageStart(EAnomalyType AnomalyType) override;

private:

};
