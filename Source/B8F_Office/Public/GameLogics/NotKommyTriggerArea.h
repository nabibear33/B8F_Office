// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/BaseArea.h"
#include "NotKommyTriggerArea.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ANotKommyTriggerArea : public ABaseArea
{
	GENERATED_BODY()

public:
	ANotKommyTriggerArea();

protected:
	virtual void BeginPlay() override;

private:
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnStageStart(EAnomalyType AnomalyType) override;

	virtual void SetNormal() override;
};
