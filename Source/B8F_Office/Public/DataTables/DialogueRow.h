// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "DialogueRow.generated.h"


USTRUCT(BlueprintType)
struct FDialogueChoice
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FText ChoiceText;

    UPROPERTY(EditAnywhere)
    FName NextRowID;
};


USTRUCT(BlueprintType)
struct FDialogueRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName SpeakerID;

    UPROPERTY(EditAnywhere)
    FText DialogueText;

    UPROPERTY(EditAnywhere)
    FName NextRowID;

    UPROPERTY(EditAnywhere)
    TArray<FDialogueChoice> Choices;
};