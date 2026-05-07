// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/EnumToRowName.h"

EnumToRowName::EnumToRowName()
{
}

EnumToRowName::~EnumToRowName()
{
}

FName EnumToRowName::Convert(FString String)
{
    FString RowNameString = UEnum::GetValueAsString(Type);
    int32 SlicingIdx;
    RowNameString.FindLastChar(':', SlicingIdx);
    RowNameString = RowNameString.RightChop(SlicingIdx + 1);
    FName RowName = FName(*RowNameString);

	return RowName;
}
