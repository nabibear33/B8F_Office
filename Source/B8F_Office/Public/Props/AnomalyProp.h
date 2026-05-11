// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "AnomalyProp.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AAnomalyProp : public ABaseProp
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

	virtual void SetNormal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<EAnomalyType> ActivatingAnomalyList;
private:
};
