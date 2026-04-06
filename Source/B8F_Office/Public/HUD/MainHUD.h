// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UDialogueComponent;
class UDialogueWidget;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowDialogueWidget(UDialogueComponent* DialogueComponent);
	void HideDialogueWidget();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	TObjectPtr<UDialogueWidget> DialogueWidget;
};
