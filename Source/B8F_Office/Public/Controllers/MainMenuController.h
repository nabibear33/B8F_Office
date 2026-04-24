// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameLogics/Types.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnClickedStartGame();

	UFUNCTION()
	void OnClickedNewGame();

	UFUNCTION()
	void OnClickedContinue();

	UFUNCTION()
	void OnClickedCollection();

	UFUNCTION()
	void OnClickedSetting();

	UFUNCTION()
	void OnClickedQuit();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	EMainMenuStatus CurrentStatus;

};
