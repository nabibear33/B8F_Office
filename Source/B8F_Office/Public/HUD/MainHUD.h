// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UDialogueWidget;
class ULeftTimeWidget;

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

	void ShowLeftTimeWidget();
	void HideLeftTimeWidget();

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDialogueWidget> DialogueWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LeftTimeWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULeftTimeWidget> LeftTimeWidget;

	// add pause widget

	// add interact widget (refactoring)

public:
	FORCEINLINE UDialogueWidget* GetDialogueWidget() { return DialogueWidget; }
};
