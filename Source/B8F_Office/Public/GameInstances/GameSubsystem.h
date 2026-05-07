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
	void OnProgressUpdated(FName Name);

	void SaveCurrentProgress();

	void ExecuteCurrentProgress(FGameProgressRow* Row);

	void UpdateManagers();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> ProgressDataTable;

	FName CurrentProgressName;

	EProgressType CurrentProgressType;

	FName CurrentLevel;

	UPROPERTY()
	TObjectPtr<AMainCharacterController> PC;

	UPROPERTY()
	TObjectPtr<ACutsceneManager> CutsceneManager;

};
