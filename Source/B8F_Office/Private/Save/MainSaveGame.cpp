// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/MainSaveGame.h"
#include "GameLogics/Types.h"

void UMainSaveGame::InitializeAnomalyRecord()
{
	AnomalyRecord.Empty();

	const UEnum* EnumPtr = StaticEnum<EAnomalyType>();
	if (!EnumPtr) return;

	for (int32 i = 0; i < EnumPtr->NumEnums() - 1; i++)
	{
		EAnomalyType Type = static_cast<EAnomalyType>(EnumPtr->GetValueByIndex(i));
		AnomalyRecord.Add(Type, EAnomalyStatus::EAS_NotSeen);
		UE_LOG(LogTemp, Warning, TEXT("[%d] Added: %s"), i, *UEnum::GetValueAsString(Type));
	}

	UE_LOG(LogTemp, Warning, TEXT("AnomalyRecord Total: %d"), AnomalyRecord.Num());
}

void UMainSaveGame::SetAnomalyRecord(EAnomalyType Type, EAnomalyStatus Status)
{
	if (!AnomalyRecord.Contains(Type))
	{
		UE_LOG(LogTemp, Warning, TEXT("SetAnomalyRecord: Non-existing AnomalyType. Add New AnomalyType"));
		AnomalyRecord.Add(Type, Status);
		return;
	}

	// Save only when higher status came in.
	AnomalyRecord[Type] = (AnomalyRecord[Type] < Status) ? Status : AnomalyRecord[Type];
}
