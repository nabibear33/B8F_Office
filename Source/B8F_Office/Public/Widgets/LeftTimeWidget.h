// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeftTimeWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ULeftTimeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnLeftTimeUpdated(float Value);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LeftTimeText;

};
