// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class B8F_OFFICE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> ProgressDataTable;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> CutsceneDataTable;
};
