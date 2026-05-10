// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/DialogueRow.h"
#include "MonologueWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UMonologueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnDialogueUpdated(const FDialogueRow& Row);

	void ResetMonologueWidget();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MonologueText;
};
