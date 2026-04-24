// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CollectedAnomalyList.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Widgets/CollectedAnomalyItem.h"
#include "Components/WrapBox.h"

void UCollectedAnomalyList::NativeConstruct()
{
	Super::NativeConstruct();

	// get savegame and add child while looping

	USaveGameInstanceSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
	UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
	const TMap<EAnomalyType, EAnomalyStatus>& AnomalyRecord = SaveGame->GetAnomalyRecord();

	for (auto& Pair : AnomalyRecord)
	{
		EAnomalyType Type = Pair.Key;
		EAnomalyStatus Status = Pair.Value;

		if (Type == EAnomalyType::EAT_Normal) continue;

		if (AnomalyItemClass)
		{
			UCollectedAnomalyItem* Item = CreateWidget<UCollectedAnomalyItem>(GetWorld(), AnomalyItemClass);
			FName RowName = FName(*UEnum::GetValueAsString(Type));
			FAnomalyRow* Row = AnomalyDataTable->FindRow<FAnomalyRow>(RowName, TEXT(""));
			if (Row)
			{
				Item->SetAnomalyName(Row->AnomalyName);
				Item->SetAnomalyImage(Row->AnomalyImage);
			}
			AnomalyItemWrapper->AddChild(Item);
		}
	}
}
