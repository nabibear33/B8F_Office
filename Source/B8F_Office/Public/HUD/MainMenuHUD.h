// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenu;
class UCollectedAnomalyList;
class UStartGameWidget;
class UBackWidget;
class UCollectedAnomalyDetail;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void EnableMainMenuWidget(bool Enabled);
	void EnableCollectionWidget(bool Enabled);
	void EnableCollectionDetailWidget(bool Enabled);
	void EnableStartGameWidget(bool Enabled);
	void EnableBackWidget(bool Enabled);

	void DisableAllWidgets();

	void OnFinishedIntroCredit();

	void OnCollectionDetailUpdated(FText AnomalyName, UTexture2D* Texture, FText AnomalyDetail);

	UFUNCTION()
	void OnMainMenuStatusUpdated(EMainMenuStatus Status);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMainMenu> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CollectionWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCollectedAnomalyList> CollectionWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CollectionDetailWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCollectedAnomalyDetail> CollectionDetailWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> StartGameWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStartGameWidget> StartGameWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BackWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBackWidget> BackWidget;


};
