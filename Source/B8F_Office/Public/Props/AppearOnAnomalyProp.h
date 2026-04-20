// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "AppearOnAnomalyProp.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AAppearOnAnomalyProp : public ABaseProp
{
	GENERATED_BODY()
	
	AAppearOnAnomalyProp();
public:

protected:
	virtual void BeginPlay() override;

private:
	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	virtual void SetNormal() override;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> MeshToAppear;
};
