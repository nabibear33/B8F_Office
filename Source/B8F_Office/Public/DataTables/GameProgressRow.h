// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameLogics/Types.h"
#include "GameProgressRow.generated.h"

class ALevelSequenceActor;

USTRUCT(BlueprintType)
struct FGameProgressRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FName ProgressSubName;

	UPROPERTY(EditAnywhere)
	EProgressType ProgressType;

	UPROPERTY(EditAnywhere)
	FName LevelName;
	
	UPROPERTY(EditAnywhere)
	FName NextProgressID;

	UPROPERTY(EditAnywhere)
	FText Description;

	// Options
	
	// Cutscene
	UPROPERTY(EditAnywhere)
	FName CutsceneName;

	// Dialogue
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(EditAnywhere)
	FName DialogueRowName;

	// Media (later)


};