// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Widgets/MainMenu/CollectedAnomalyItem.h"
#include "Widgets/MainMenu/CollectedAnomalyDetail.h"
#include "Components/WrapBox.h"
#include "Helper/EnumToRowName.h"

void UCollectedAnomalyList::NativeConstruct()
{
    Super::NativeConstruct();

    USaveSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
    UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
    const TMap<EAnomalyType, EAnomalyStatus>& AnomalyRecord = SaveGame->GetAnomalyRecord();
    
    for (auto& Pair : AnomalyRecord)
    {
        EAnomalyType Type = Pair.Key;
        EAnomalyStatus Status = Pair.Value;

        if (Type == EAnomalyType::EAT_None || Type == EAnomalyType::EAT_MAX) continue;

        UCollectedAnomalyItem* Item = CreateWidget<UCollectedAnomalyItem>(GetWorld(), AnomalyItemClass);

        FName RowName = EnumToRowName::Convert(Type);

        FAnomalyRow* Row = AnomalyDataTable->FindRow<FAnomalyRow>(RowName, TEXT(""));
        if (Row)
        {
            UE_LOG(LogTemp, Log, TEXT("[CollectedAnomaly] Row found: %s"), *Row->AnomalyName.ToString());
            if (Status == EAnomalyStatus::EAS_Found)
            {
                Item->SetAnomalyName(Row->AnomalyName);
                Item->SetAnomalyImage(Row->AnomalyImage);
                Item->SetAnomalyDetail(Row->AnomalyDescription);
            }
            else
            {
                Item->SetAnomalyName(FText::FromString("???"));
                Item->SetAnomalyImage(NotSeenTexture);
                Item->SetAnomalyDetail(FText::FromString("???"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("[CollectedAnomaly] No DataTable row found for RowName: %s"), *RowName.ToString());
        }

        AnomalyItemWrapper->AddChild(Item);
    }
}
