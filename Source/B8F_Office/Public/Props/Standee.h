// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "Standee.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AStandee : public ABaseProp
{
	GENERATED_BODY()

	AStandee();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StandeeMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> ButterMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> RanMesh;

	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	void SetRanMesh();

	virtual void SetNormal() override;
	
};
