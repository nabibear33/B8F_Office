// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "BaseCharacter.generated.h"

class UInteractComponent;
class AMainCharacter;

UCLASS()
class B8F_OFFICE_API ABaseCharacter : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FText GetInteractHintText() override;

protected:
	virtual void BeginPlay() override;

	virtual void SetNormal();

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

private:	
	UPROPERTY(EditAnywhere)
	bool bIsInteractable = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInteractComponent> InteractComponent;


};
