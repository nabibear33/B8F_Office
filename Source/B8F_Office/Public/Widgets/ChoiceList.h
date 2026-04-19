// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/DialogueRow.h"
#include "ChoiceList.generated.h"

class UChoiceItem;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UChoiceList : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetChoiceItems(const FDialogueRow& Row);

	UFUNCTION()
	void OnCurrentHighlightedChoiceUpdated(int32 CurrentHighlightedChoiceIndex);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ChoiceItemWrapper;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChoiceItem> ChoiceItemClass;

	UPROPERTY()
	TArray<TObjectPtr<UChoiceItem>> ChoiceItems;
};
