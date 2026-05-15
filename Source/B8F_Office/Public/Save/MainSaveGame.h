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
	FORCEINLINE void SetMainStageFloor(int32 Value) { MainStageFloor = Value; }
	FORCEINLINE void NormalStageCleared() { bHasClearedNormalStage = true; }
	FORCEINLINE void CollectedAll() { bHasCollectedAll = true; }
	FORCEINLINE void FirstPlay() { bHasPlayedBefore = true; }
	FORCEINLINE void SetProgressName(FName Name) { GameProgressRowName = Name; }

	FORCEINLINE int32 GetMainStageFloor() { return MainStageFloor; }
	FORCEINLINE bool IsNormalStageCleared() { return bHasClearedNormalStage; }
	FORCEINLINE bool HasCollectedAll() { return bHasCollectedAll; }
	FORCEINLINE bool HasPlayedBefore() { return bHasPlayedBefore; }
	FORCEINLINE const TArray<FAnomalyEntry>& GetAnomalyRecord() { return AnomalyRecord; }
	FORCEINLINE FName GetProgressName() { return GameProgressRowName; }

	void SetAllAnomalyUnSeen();
	void SetAnomalyRecord(EAnomalyType Type, EAnomalyStatus Status);

	void PrintSaveData() const;

private:
	UPROPERTY(SaveGame)
	FName GameProgressRowName;

	UPROPERTY(SaveGame)
	int MainStageFloor;
	
	UPROPERTY(SaveGame)
	TArray<FAnomalyEntry> AnomalyRecord;

	UPROPERTY(SaveGame)
	bool bHasClearedNormalStage = false;

	UPROPERTY(SaveGame)
	bool bHasCollectedAll = false;

	UPROPERTY(SaveGame)
	bool bHasPlayedBefore = false;
};
