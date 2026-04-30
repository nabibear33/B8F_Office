// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLogics/Types.h"
#include "GameSubsystem.generated.h"

class FSubsystemCollectionBase;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SetCurrentProgress(FName Name, EProgressType Type);

private:

	FName CurrentProgressName;

	EProgressType CurrentProgressType;

};
