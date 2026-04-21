// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/Delegates.h"
#include "Characters/InteractableCharacter.h"
#include "Madeleine.generated.h"

class UAnimMontage;
class UDataTable;
class UCameraComponent;
class ATriggerArea;

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
	virtual void OnStageStart(EAnomalyType AnomalyType) override;

private:
	UFUNCTION()
	void StartGame(AActor* TriggeringArea, AActor* OtherActor);

	UFUNCTION()
	void OnDialogueEnded();

	void StartDialogue(FName ID);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> FinishArea;

	UPROPERTY(VisibleAnywhere)
	bool bPlayerWinRedLight = false;

	UFUNCTION()
	void PlayerWinRedLight(AActor* TriggeringArea, AActor* OtherActor);
};
