// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Delegates.h"
#include "GameManager.generated.h"



class AStageStartArea;
class ATeleportArea;
class AStageManager;
class ATriggerArea;
class AMainCharacter;
class ACutsceneManager;
class ANotKommy;
class USaveGameInstanceSubsystem;
class UMainSaveGame;

UCLASS()
class B8F_OFFICE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

	UPROPERTY()
	FOnInfoPanelChanged OnInfoPanelUpdated;

	FVector GetPlayerLocation();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AStageStartArea> StageStartAreaUp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AStageStartArea> StageStartAreaDown;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ANotKommy> NotKommy;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> NotKommyTriggerArea;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AMainCharacter> Player;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATeleportArea> TeleportAreaUp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<ATeleportArea> TeleportAreaDown;



	UFUNCTION()
	void OnStageStartAreaTriggered(AActor* TriggeringArea, AActor* OtherActor);

	UFUNCTION()
	void OnTeleportAreaTriggered(AActor* TriggeringArea, AActor* OtherActor);

	UFUNCTION()
	void OnPlayDeathScene(EDeathSceneType DeathSceneType);

	UFUNCTION()
	void OnPlayerDeathAndReset();


	UPROPERTY(EditAnywhere)
	TObjectPtr<AStageManager> StageManager;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ACutsceneManager> CutsceneManager;

	UPROPERTY(VisibleAnywhere)
	bool bHasFirstEntered;

	void HandlePlayerChoice(ATeleportArea* AreaPlayerEntered);

	bool IsCorrect(EStageState StageState, ATeleportArea*& AreaPlayerEntered);

	void SaveData();

	void InitializeInfoPanel();

	void UpdateInfoPanel(int32 Floor, EAnomalyType AnomalyType, EAnomalyStatus AnomalyStatus);

	UPROPERTY(VisibleAnywhere)
	TMap<EAnomalyType, EAnomalyStatus> AnomalyRecord;

	TObjectPtr<USaveGameInstanceSubsystem> SaveSubsystem;

	TObjectPtr<UMainSaveGame> SaveGame;

	
public:
	FORCEINLINE AStageManager* GetStageManager() { return StageManager; }
};
