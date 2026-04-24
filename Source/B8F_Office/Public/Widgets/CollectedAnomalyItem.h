// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectedAnomalyItem.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UCollectedAnomalyItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAnomalyName(FText Text);

	void SetAnomalyImage(UTexture2D* Texture);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnomalyName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AnomalyImage;

	// add click for liking detail widget
};
