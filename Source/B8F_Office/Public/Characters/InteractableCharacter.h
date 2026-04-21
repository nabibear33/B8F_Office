// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Interactable.h"
#include "GameLogics/Types.h"
#include "InteractableCharacter.generated.h"

class UInteractComponent;
class AMainCharacter;
class ATriggerArea;

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

protected:
	virtual void BeginPlay() override;

	virtual void SetNormal();

	void DisableCharacterMesh();

	void EnableCharacterMesh();

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> LinkedArea;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInteractComponent> InteractComponent;
private:


	UFUNCTION()
	void OnInteractableEntered(AActor* InteractableActor, AMainCharacter* MainCharacter);

	UFUNCTION()
	void OnInteractableLeft(AActor* InteractableActor, AMainCharacter* MainCharacter);

	UPROPERTY(EditAnywhere)
	bool bIsInInteractRange = false;

	
public:
	FORCEINLINE bool GetIsInteractable() { return bIsInInteractRange; }
	FORCEINLINE UInteractComponent* GetInteractComponent() { return InteractComponent; }
};
