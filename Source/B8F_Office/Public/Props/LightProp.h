// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "LightProp.generated.h"

class ULightComponent;

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

	UFUNCTION()
	void OnLightColorChanged(FLinearColor Color);

protected:
	virtual void BeginPlay() override;

private:
	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	virtual void SetNormal() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULightComponent> LightComponentClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ULightComponent> LightComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ALightProp> LinkedLightProp;

	FTimerHandle LightOffTimerHandle;
};
