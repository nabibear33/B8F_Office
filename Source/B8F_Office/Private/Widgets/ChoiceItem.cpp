// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ChoiceItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UChoiceItem::SetChoiceText(const FText& Text)
{
    UE_LOG(LogTemp, Warning, TEXT("SetChoiceText called"));

    if (!ChoiceText)
    {
        UE_LOG(LogTemp, Error, TEXT("ChoiceText BindWidget is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Setting text: %s"), *Text.ToString());
    ChoiceText->SetText(Text);
}

void UChoiceItem::HighlightChoice(bool bHighlight)
{
    if (bHighlight)
    {
        ChoiceText->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
        TextBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 0.f, 0.5f));
    }
    else
    {
        ChoiceText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
        TextBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
    }
}