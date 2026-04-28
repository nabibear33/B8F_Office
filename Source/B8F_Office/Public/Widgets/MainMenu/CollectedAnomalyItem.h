// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLogics/Delegates.h"
#include "CollectedAnomalyItem.generated.h"

class UTextBlock;
class UImage;
class UButton;

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

	void SetAnomalyDetail(FText Text);
	
	UFUNCTION()
	void OnClickedCollectionDetail();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnomalyName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AnomalyImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DetailButton;

	FOnCollectionItemClicked OnCollectionItemClicked;

	UPROPERTY()
	FText CachedAnomalyName;

	UPROPERTY()
	FText CachedAnomalyDetail;

	UPROPERTY()
	TObjectPtr<UTexture2D> CachedAnomalyTexture;
};
