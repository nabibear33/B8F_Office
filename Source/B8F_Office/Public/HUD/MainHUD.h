// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameLogics/Types.h"
#include "MainHUD.generated.h"

class UDialogueWidget;
class ULeftTimeWidget;
class UMonologueWidget;
class UInteractWidget;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowDialogueWidget();
	void HideDialogueWidget();

	void ShowMonologueWidget();
	void HideMonologueWidget();

	void ShowLeftTimeWidget();
	void HideLeftTimeWidget();

	void ShowInteractWidget();
	void HideInteractWidget();

	UFUNCTION()
	void OnInteractableUpdated(AActor* InteractableActor, FVector ActorLocation, FText InteractText);

	UFUNCTION()
	void OnInteractableLeft(AActor* InteractableActor);

	UFUNCTION()
	void OnGamePhaseUpdated(EGamePhase Phase);

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDialogueWidget> DialogueWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MonologueWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMonologueWidget> MonologueWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LeftTimeWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULeftTimeWidget> LeftTimeWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInteractWidget> InteractWidget;

	// add pause widget

	// add interact widget (refactoring)


public:
	FORCEINLINE UDialogueWidget* GetDialogueWidget() { return DialogueWidget; }
	FORCEINLINE UMonologueWidget* GetMonologueWidget() { return MonologueWidget; }
};
