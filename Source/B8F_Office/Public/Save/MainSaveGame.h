// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameLogics/Types.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetCurrentFloor(int32 Value) { MainStageStatus.CurrentFloor = Value; }
	FORCEINLINE void NormalStageCleared() { bHasClearedNormalStage = true; }
	FORCEINLINE void CollectedAll() { bHasCollectedAll = true; }
	FORCEINLINE void FirstPlay() { bHasPlayedBefore = true; }
	FORCEINLINE void SetProgressName(FName Name) { GameProgressRowName = Name; }

	FORCEINLINE int32 GetCurrentFloor() { return MainStageStatus.CurrentFloor; }
	FORCEINLINE bool IsNormalStageCleared() { return bHasClearedNormalStage; }
	FORCEINLINE bool HasCollectedAll() { return bHasCollectedAll; }
	FORCEINLINE bool HasPlayedBefore() { return bHasPlayedBefore; }
	FORCEINLINE const TMap<EAnomalyType, EAnomalyStatus>& GetAnomalyRecord() { return MainStageStatus.AnomalyRecord; }
	FORCEINLINE FName GetProgressName() { return GameProgressRowName; }

	void InitializeAnomalyRecord();
	void SetAnomalyRecord(EAnomalyType Type, EAnomalyStatus Status);

private:
	UPROPERTY()
	FName GameProgressRowName = FName(TEXT("NotStarted"));

	UPROPERTY()
	FMainStageStatus MainStageStatus;

	UPROPERTY()
	bool bHasClearedNormalStage = false;

	UPROPERTY()
	bool bHasCollectedAll = false;

	UPROPERTY()
	bool bHasPlayedBefore = false;
};
