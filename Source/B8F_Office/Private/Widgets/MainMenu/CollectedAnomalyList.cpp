// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Widgets/MainMenu/CollectedAnomalyItem.h"
#include "Components/WrapBox.h"

void UCollectedAnomalyList::NativeConstruct()
{
	//Super::NativeConstruct();

	//USaveGameInstanceSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
	//UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
	//const TMap<EAnomalyType, EAnomalyStatus>& AnomalyRecord = SaveGame->GetAnomalyRecord();

	//for (auto& Pair : AnomalyRecord)
	//{
	//	EAnomalyType Type = Pair.Key;
	//	EAnomalyStatus Status = Pair.Value;

	//	if (Type == EAnomalyType::EAT_None) continue;

	//	if (AnomalyItemClass)
	//	{
	//		UCollectedAnomalyItem* Item = CreateWidget<UCollectedAnomalyItem>(GetWorld(), AnomalyItemClass);
	//		FName RowName = FName(*UEnum::GetValueAsString(Type));
	//		FAnomalyRow* Row = AnomalyDataTable->FindRow<FAnomalyRow>(RowName, TEXT(""));
	//		if (Row)
	//		{
	//			Item->SetAnomalyName(Row->AnomalyName);
	//			Item->SetAnomalyImage(Row->AnomalyImage);
	//		}
	//		AnomalyItemWrapper->AddChild(Item);
	//	}
	//}

    Super::NativeConstruct();

    USaveGameInstanceSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
    if (!SaveSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("[CollectedAnomaly] SaveSubsystem is null"));
        return;
    }

    UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
    if (!SaveGame)
    {
        UE_LOG(LogTemp, Error, TEXT("[CollectedAnomaly] SaveGame is null"));
        return;
    }

    const TMap<EAnomalyType, EAnomalyStatus>& AnomalyRecord = SaveGame->GetAnomalyRecord();
    UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] AnomalyRecord count: %d"), AnomalyRecord.Num());

    for (auto& Pair : AnomalyRecord)
    {
        EAnomalyType Type = Pair.Key;
        EAnomalyStatus Status = Pair.Value;

        if (Type == EAnomalyType::EAT_None || Type == EAnomalyType::EAT_MAX) continue;

        UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] Type: %s | Status: %s"),
            *UEnum::GetValueAsString(Type),
            *UEnum::GetValueAsString(Status));

        if (!AnomalyItemClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("[CollectedAnomaly] AnomalyItemClass is null, skipping"));
            continue;
        }

        UCollectedAnomalyItem* Item = CreateWidget<UCollectedAnomalyItem>(GetWorld(), AnomalyItemClass);
        if (!Item)
        {
            UE_LOG(LogTemp, Error, TEXT("[CollectedAnomaly] Failed to create widget for Type: %s"),
                *UEnum::GetValueAsString(Type));
            continue;
        }

        if (!AnomalyDataTable)
        {
            UE_LOG(LogTemp, Error, TEXT("[CollectedAnomaly] AnomalyDataTable is null"));
            continue;
        }

        FName RowName = FName(*UEnum::GetValueAsString(Type));
        FAnomalyRow* Row = AnomalyDataTable->FindRow<FAnomalyRow>(RowName, TEXT(""));
        if (Row)
        {
            UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] Row found: %s"), *Row->AnomalyName.ToString());
            Item->SetAnomalyName(Row->AnomalyName);
            Item->SetAnomalyImage(Row->AnomalyImage);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("[CollectedAnomaly] No DataTable row found for RowName: %s"), *RowName.ToString());
        }

        AnomalyItemWrapper->AddChild(Item);
        UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] Item added to wrapper"));
    }

    UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] NativeConstruct complete"));
}
