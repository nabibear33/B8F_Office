// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameLogics/Types.h"
#include "AnomalyRow.generated.h"

USTRUCT(BlueprintType)
struct FAnomalyRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    EAnomalyType AnomalyType;

    UPROPERTY(EditAnywhere)
    FText AnomalyName;

    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UTexture2D> AnomalyImage;

    UPROPERTY(EditAnywhere)
    FText AnomalyDescription;
};