// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "LightProp.generated.h"

class URectLightComponent;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ALightProp : public ABaseProp
{
	GENERATED_BODY()
	
	ALightProp();

public:
	UFUNCTION()
	void AnomalyLightOff(AActor* TriggeringActor, AActor* TriggeredCharacter);

protected:
	virtual void BeginPlay() override;

private:
	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	virtual void SetNormal() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<URectLightComponent> RectLightComponent;

	UPROPERTY(EditAnywhere)
	float AnomalyLightIntensity;

	UPROPERTY(EditAnywhere)
	FLinearColor AnomalyLightColor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ALightProp> LinkedLightProp;

	FTimerHandle LightOffTimerHandle;
};
