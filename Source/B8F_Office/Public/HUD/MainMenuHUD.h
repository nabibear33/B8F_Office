// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenu;
class UCollectedAnomalyList;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowMainMenuWidget();
	void HideMainMenuWidget();

	// show, hide other widgets too.

	void OnFinishedIntroCredit();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CollectedAnomalyWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCollectedAnomalyList> CollectedAnomalyWidget;

	// add game start widget, setting widget later
};
