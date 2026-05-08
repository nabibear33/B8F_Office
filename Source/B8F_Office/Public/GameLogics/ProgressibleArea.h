// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/BaseArea.h"
#include "GameLogics/Delegates.h"
#include "Interfaces/Progressible.h"
#include "ProgressibleArea.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AProgressibleArea : public ABaseArea, public IProgressible
{
	GENERATED_BODY()
	
public:
	FOnGameProgressUpdated OnGameProgressUpdated;

	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	virtual void AdvanceProgress(FName Name) override;

	UPROPERTY(EditAnywhere)
	FName LinkedProgressName;
};
