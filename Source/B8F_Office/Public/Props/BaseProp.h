// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "BaseProp.generated.h"

UCLASS()
class B8F_OFFICE_API ABaseProp : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProp();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

	virtual void SetNormal();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
};
