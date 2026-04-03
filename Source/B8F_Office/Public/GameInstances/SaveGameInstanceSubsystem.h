// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameInstanceSubsystem.generated.h"

class UMainSaveGame;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API USaveGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SaveGame();
	void LoadGame();

	FORCEINLINE UMainSaveGame* GetSaveGame() const { return CurrentSaveGame; }

	void CreateNewSaveGame();

private:
	
	UPROPERTY()
	TObjectPtr<UMainSaveGame> CurrentSaveGame;

	const FString SaveSlotName = TEXT("MainSaveSlot");
	const int32 UserIndex = 0;
};
