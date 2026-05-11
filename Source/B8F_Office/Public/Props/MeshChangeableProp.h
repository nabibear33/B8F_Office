// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/AnomalyProp.h"
#include "MeshChangeableProp.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMeshChangeableProp : public AAnomalyProp
{
	GENERATED_BODY()

	AMeshChangeableProp();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ChangeableMeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> NormalMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> AnomalyMesh;

	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	void SetAnomalyMesh();

	virtual void SetNormal() override;
	
};
