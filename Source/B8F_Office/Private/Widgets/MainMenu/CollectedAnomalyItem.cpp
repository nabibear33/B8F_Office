// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/CollectedAnomalyItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCollectedAnomalyItem::SetAnomalyName(FText Text)
{
	AnomalyName->SetText(Text);
}

void UCollectedAnomalyItem::SetAnomalyImage(UTexture2D* Texture)
{
	AnomalyImage->SetBrushFromTexture(Texture);
}