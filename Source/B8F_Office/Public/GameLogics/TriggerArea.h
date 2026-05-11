// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/BaseArea.h"
#include "GameLogics/Types.h"
#include "TriggerArea.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ATriggerArea : public ABaseArea
{
	GENERATED_BODY()

public:
	ATriggerArea();

protected:
	virtual void BeginPlay() override;

private:
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	UFUNCTION()
	void OnStageStart(EAnomalyType AnomalyType);

	void SetNormal();

	UPROPERTY(EditAnywhere)
	EAnomalyType LinkedAnomalyType;
};
