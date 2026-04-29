// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectedAnomalyDetail.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UCollectedAnomalyDetail : public UUserWidget
{
	GENERATED_BODY()

public:
	void AnomalyDetailUpdated(FText _AnomalyName, UTexture2D* Texture, FText _AnomalyDetail);
	
	void SetAnomalyName(FText Text);

	void SetAnomalyDetail(FText Text);

	void SetImage(UTexture2D* Texture);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnomalyName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AnomalyImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnomalyDetail;
};
