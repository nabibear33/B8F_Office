// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/MainSaveGame.h"
#include "GameLogics/Types.h"

void UMainSaveGame::InitializeAnomalyRecord()
{
	MainStageStatus.AnomalyRecord.Empty();

	const UEnum* EnumPtr = StaticEnum<EAnomalyType>();
	if (!EnumPtr) return;

	for (int32 i = 0; i < EnumPtr->NumEnums() - 1; i++)
	{
		EAnomalyType Type = static_cast<EAnomalyType>(EnumPtr->GetValueByIndex(i));
		MainStageStatus.AnomalyRecord.Add(Type, EAnomalyStatus::EAS_NotSeen);
		UE_LOG(LogTemp, Warning, TEXT("[%d] Added: %s"), i, *UEnum::GetValueAsString(Type));
	}

	UE_LOG(LogTemp, Warning, TEXT("AnomalyRecord Total: %d"), MainStageStatus.AnomalyRecord.Num());
}

void UMainSaveGame::SetAnomalyRecord(EAnomalyType Type, EAnomalyStatus Status)
{
	if (!MainStageStatus.AnomalyRecord.Contains(Type))
	{
		UE_LOG(LogTemp, Warning, TEXT("SetAnomalyRecord: Non-existing AnomalyType. Add New AnomalyType"));
		MainStageStatus.AnomalyRecord.Add(Type, Status);
		return;
	}

	// Save only when higher status came in.
	MainStageStatus.AnomalyRecord[Type] = (MainStageStatus.AnomalyRecord[Type] < Status) ? Status : MainStageStatus.AnomalyRecord[Type];
}
