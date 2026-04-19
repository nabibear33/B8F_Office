// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoiceItem.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UChoiceItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetChoiceText(const FText& Text);

	void HighlightChoice(bool bHighlight);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ChoiceText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> TextBackground;
	
};
