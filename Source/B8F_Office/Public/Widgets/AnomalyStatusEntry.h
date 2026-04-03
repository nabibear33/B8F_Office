// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLogics/Types.h"
#include "AnomalyStatusEntry.generated.h"

class UImage;
class UTextBlock;


/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UAnomalyStatusEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateEntry(EAnomalyType Type, EAnomalyStatus Status);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> EntryImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> EntryText;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAnomalyStatus, TObjectPtr<UTexture2D>> StatusTextureMap;

	EAnomalyType AnomalyType;
	EAnomalyStatus AnomalyStatus;

private:
	virtual void NativeConstruct() override;
};
