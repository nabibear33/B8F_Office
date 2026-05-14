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
class UUserWidget;
class UPauseWidget;
class UCollectedAnomalyList;
class UOptionWidget;
class AMainCharacterController;
class UBackWidget;

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

	void SetWidgetVisibility(UUserWidget* Widget, bool Enabled);

	UFUNCTION()
	void OnInteractableUpdated(AActor* InteractableActor, FVector ActorLocation, FText InteractText);

	UFUNCTION()
	void OnInteractableLeft(AActor* InteractableActor);

	UFUNCTION()
	void OnGamePhaseUpdated(EGamePhase Phase);

	UFUNCTION()
	void OnPauseStatusUpdated(EPauseStatus Status);

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPauseWidget> PauseWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CollectionWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCollectedAnomalyList> CollectionWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SettingWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOptionWidget> SettingWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BackWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBackWidget> BackWidget;

	void DisableAllWidgets();


	template<typename T>
	T* CreateWidgetFromWidgetClass(AMainCharacterController* PC, TSubclassOf<UUserWidget> WidgetClass)
	{
		if (!WidgetClass) return nullptr;

		T* Widget = CreateWidget<T>(PC, WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
		return Widget;
	}

public:
	FORCEINLINE UDialogueWidget* GetDialogueWidget() { return DialogueWidget; }
	FORCEINLINE UMonologueWidget* GetMonologueWidget() { return MonologueWidget; }
};
