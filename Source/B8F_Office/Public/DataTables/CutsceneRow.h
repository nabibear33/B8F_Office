// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameLogics/Types.h"
#include "LevelSequence.h"
#include "CutsceneRow.generated.h"

USTRUCT(BlueprintType)
struct FCutsceneRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    ECutsceneName CutsceneName = ECutsceneName::ECN_None;

    UPROPERTY(EditAnywhere)
    ECutsceneType CutsceneType = ECutsceneType::ECT_Normal;

    UPROPERTY(EditAnywhere)
    TObjectPtr<ULevelSequence> LevelSequence;
};