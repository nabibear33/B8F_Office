// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AnomalyStatusEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UAnomalyStatusEntry::UpdateEntry(EAnomalyType Type, EAnomalyStatus Status)
{
    /*
    UE_LOG(LogTemp, Warning, TEXT("UpdateEntry called - Type: %s, Status: %s"),
        *UEnum::GetValueAsString(Type),
        *UEnum::GetValueAsString(Status));
    */

    if (!EntryText)
    {
        UE_LOG(LogTemp, Error, TEXT("EntryText is null"));
        return;
    }
    EntryText->SetText(FText::FromString(UEnum::GetValueAsString(Type)));

    // UE_LOG(LogTemp, Warning, TEXT("StatusTextureMap count: %d"), StatusTextureMap.Num());

    if (TObjectPtr<UTexture2D>* Found = StatusTextureMap.Find(Status))
    {
        if (*Found)
        {
            // UE_LOG(LogTemp, Warning, TEXT("Texture found: %s"), *(*Found)->GetName());
            EntryImage->SetBrushFromTexture(*Found);
            EntryImage->SetColorAndOpacity(FLinearColor::Red);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Texture is null for Status: %s"), *UEnum::GetValueAsString(Status));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Status not found in StatusTextureMap: %s"), *UEnum::GetValueAsString(Status));
    }
}

void UAnomalyStatusEntry::NativeConstruct()
{
	Super::NativeConstruct();


}
