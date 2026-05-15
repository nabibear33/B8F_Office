// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/MainSaveGame.h"
#include "GameLogics/Types.h"

void UMainSaveGame::SetAllAnomalyUnSeen()
{
	AnomalyRecord.Empty();

	for (uint8 i = 1; i < (uint8)EAnomalyType::EAT_MAX; i++)
	{
		AnomalyRecord.Add(FAnomalyEntry{ (EAnomalyType)i, EAnomalyStatus::EAS_NotSeen });
	}

	UE_LOG(LogTemp, Warning, TEXT("AnomalyRecord Total: %d"), AnomalyRecord.Num());
}

void UMainSaveGame::SetAnomalyRecord(EAnomalyType Type, EAnomalyStatus Status)
{
	// Save only when higher status came in. (Not Seen < Seen But Not Found < Fully Solved)
	int32 Index = (int32)(uint8)Type - 1;
	FAnomalyEntry& Entry = AnomalyRecord[Index];
	Entry.Status = FMath::Max(Entry.Status, Status);
}

void UMainSaveGame::PrintSaveData() const
{
	UE_LOG(LogTemp, Warning, TEXT("========== [SaveGame Data] =========="));
	UE_LOG(LogTemp, Warning, TEXT("GameProgressRowName : %s"), *GameProgressRowName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("bHasClearedNormalStage : %s"), bHasClearedNormalStage ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Warning, TEXT("bHasCollectedAll       : %s"), bHasCollectedAll ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Warning, TEXT("bHasPlayedBefore       : %s"), bHasPlayedBefore ? TEXT("true") : TEXT("false"));

	// MainStageStatus
	UE_LOG(LogTemp, Warning, TEXT("--- MainStageStatus ---"));
	UE_LOG(LogTemp, Warning, TEXT("CurrentFloor : %d"), MainStageFloor);  // 필드명은 실제 구조체에 맞게 수정
	// AnomalyMap 등 TMap이 있다면:
	for (const FAnomalyEntry& Entry : AnomalyRecord)
	{
		UE_LOG(LogTemp, Warning, TEXT("  Anomaly [%s] = %s"),
			*StaticEnum<EAnomalyType>()->GetNameStringByValue((int64)Entry.Type),
			*StaticEnum<EAnomalyStatus>()->GetNameStringByValue((int64)Entry.Status));
	}
	UE_LOG(LogTemp, Warning, TEXT("====================================="));
}
