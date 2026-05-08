// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLogics/Types.h"
#include "DataTables/GameProgressRow.h"
#include "GameSubsystem.generated.h"

class AMainCharacterController;
class ACutsceneManager;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnGameProgressUpdated(FName Name);

	UFUNCTION()
	void OnGamePhaseUpdated(EGamePhase Phase);

	void SaveCurrentProgress();

	void ExecuteCurrentProgress(FGameProgressRow* Row);

	void UpdateManagers();

	UPROPERTY(BlueprintReadOnly)
	FName CurrentProgressName;

	UPROPERTY(BlueprintReadOnly)
	EGamePhase CurrentGamePhase;

	UPROPERTY(BlueprintReadOnly)
	FName CurrentLevel;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> ProgressDataTable;

	UPROPERTY()
	TObjectPtr<AMainCharacterController> PlayerController;

	UPROPERTY()
	TObjectPtr<ACutsceneManager> CutsceneManager;

public:
	FORCEINLINE void SetCutsceneManager(ACutsceneManager* Manager) { CutsceneManager = Manager; }
	FORCEINLINE void SetPlayerController(AMainCharacterController* Controller) { PlayerController = Controller; }

};
