// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "MirrorProp.generated.h"

class USceneCaptureComponent2D;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMirrorProp : public ABaseProp
{
	GENERATED_BODY()

public:
	AMirrorProp();
protected:
	virtual void BeginPlay() override;
	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	virtual void Tick(float Deltatime) override;
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MirrorMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MID;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextureRenderTarget2D> RenderTarget;

};
