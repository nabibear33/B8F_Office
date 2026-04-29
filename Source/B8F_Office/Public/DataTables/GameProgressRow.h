// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameLogics/Types.h"
#include "GameProgressRow.generated.h"

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
};