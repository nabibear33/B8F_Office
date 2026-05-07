// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogics/Types.h"

/**
 * 
 */
class B8F_OFFICE_API EnumToRowName
{
public:
	EnumToRowName();
	~EnumToRowName();

	FName Convert(FString String);
};
