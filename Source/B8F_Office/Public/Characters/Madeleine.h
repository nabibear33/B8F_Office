// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/Delegates.h"
#include "GameLogics/Types.h"
#include "Characters/InteractableCharacter.h"
#include "Madeleine.generated.h"

class UAnimMontage;
class UDataTable;
class UCameraComponent;
class ATriggerArea;
class AMainCharacter;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMadeleine : public AInteractableCharacter
{
	GENERATED_BODY()

	AMadeleine();
	
public:
	FOnPlayDeathScene OnPlayDeathScene;

protected:
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	virtual void Tick(float DeltaTime) override;
	void CheckMovement();
	void CheckLeftTime(float DeltaTime);
	virtual void OnStageStart(EAnomalyType AnomalyType) override;

private:

	UFUNCTION()
	void OnAreaTriggered(AActor* TriggeringArea, AActor* OtherActor);

	void SetViewTargetChanged();

	UFUNCTION()
	void OnDialogueEnded(FName DialogueID);

	void StartDialogue(FName ID);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> FinishArea;

	UPROPERTY(VisibleAnywhere)
	bool bPlayerWinRedLight = false;

	UFUNCTION()
	void OnFinishAreaTriggerd(AActor* TriggeringArea, AActor* OtherActor);

	void OnPassedGame();

	UPROPERTY(VisibleAnywhere)
	bool bIsViewTargetChanged = false;

	UPROPERTY(VisibleAnywhere)
	ERedLightStageStatus StageStatus;

	void OnPhaseTransition(ERedLightStageStatus Status);

	void OnStageEntered();

	void MainGame();

	UPROPERTY(VisibleAnywhere)
	bool bIsRedLight = false;

	UPROPERTY(VisibleAnywhere)
	float TimeLeft = 10.f;

	UPROPERTY()
	TObjectPtr<AMainCharacter> CachedPlayer;

	void LoseGame(FName RowName);

	FORCEINLINE void SetPhase(ERedLightStageStatus Status) { StageStatus = Status; }
};
