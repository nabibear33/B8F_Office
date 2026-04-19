// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "Interfaces/Interactable.h"
#include "BaseProp.generated.h"

class ATriggerArea;
class UInteractComponent;

UCLASS()
class B8F_OFFICE_API ABaseProp : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABaseProp();

	virtual UInteractComponent* GetInteractComponent() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

	virtual void SetNormal();

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> LinkedArea;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(EditAnywhere)
	bool bIsInteractable = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInteractComponent> InteractComponent;

};
