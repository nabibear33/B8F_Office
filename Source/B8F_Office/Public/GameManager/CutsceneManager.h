// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "CutsceneManager.generated.h"

class ALevelSequenceActor;

UCLASS()
class B8F_OFFICE_API ACutsceneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACutsceneManager();
	virtual void Tick(float DeltaTime) override;

	void PlayDeathScene(EDeathSceneType DeathSceneType);

	FOnPlayerDeathAndReset OnPlayerDeathAndReset;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TMap<EDeathSceneType, TObjectPtr<ALevelSequenceActor>> DeathScenes;

	UFUNCTION()
	void OnCutsceneFinished();
};
