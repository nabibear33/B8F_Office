// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Interactable.h"
#include "GameLogics/Types.h"
#include "InteractableCharacter.generated.h"

class UInteractComponent;
class AMainCharacter;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AInteractableCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableCharacter();

	virtual FText GetInteractHintText() override;

	virtual UInteractComponent* GetInteractComponent() override;

protected:
	virtual void BeginPlay() override;

	virtual void SetNormal();

	void DisableCharacterMesh();

	void EnableCharacterMesh();

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

private:


	UFUNCTION()
	void OnInteractableEntered(AActor* InteractableActor, AMainCharacter* MainCharacter);

	UFUNCTION()
	void OnInteractableLeft();

	UPROPERTY(EditAnywhere)
	bool bIsInteractable = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInteractComponent> InteractComponent;
	
};
