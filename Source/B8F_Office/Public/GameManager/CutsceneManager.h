// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "CutsceneManager.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;

UCLASS()
class B8F_OFFICE_API ACutsceneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACutsceneManager();
	virtual void Tick(float DeltaTime) override;

	void PlayCutscene(FName RowName);

	FOnPlayerDeath OnPlayerDeath;

	FOnPlayerRevive OnPlayerRevive;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDeathsceneFinished();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> CutsceneDataTable;

	UPROPERTY()
	TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer;

	UPROPERTY()
	TObjectPtr<ALevelSequenceActor> LevelSequenceActor;
};
