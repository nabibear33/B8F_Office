// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/InteractableCharacter.h"
#include "DataTables/DialogueRow.h"
#include "Renewa.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ARenewa : public AInteractableCharacter
{
	GENERATED_BODY()

public:

private:
	virtual void Interact_Implementation() override;

	virtual void OnStageStart(EAnomalyType AnomalyType) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> DialogueDataTable;
};
