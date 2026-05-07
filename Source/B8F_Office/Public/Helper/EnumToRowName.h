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

    template<typename TEnum>
    static FName Convert(TEnum Type)
    {
        FString RowNameString = UEnum::GetValueAsString(Type);
        int32 SlicingIdx;
        RowNameString.FindLastChar(':', SlicingIdx);
        RowNameString = RowNameString.RightChop(SlicingIdx + 1);
        FName RowName = FName(*RowNameString);

        return RowName;
    }
};
