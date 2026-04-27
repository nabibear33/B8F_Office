// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CollectionModeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MarathonModeButton;
};
