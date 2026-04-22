// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLogics/Delegates.h"
#include "EventBusSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UEventBusSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	FOnLeftTimeUpdated OnLeftTimeUpdated;
};
