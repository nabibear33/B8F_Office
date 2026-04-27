// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/CollectedAnomalyDetail.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCollectedAnomalyDetail::SetAnomalyName(FText Text)
{
	AnomalyName->SetText(Text);
}

void UCollectedAnomalyDetail::SetAnomalyDetail(FText Text)
{
	AnomalyDetail->SetText(Text);
}

void UCollectedAnomalyDetail::SetImage(UTexture2D* Texture)
{
	AnomalyImage->SetBrushFromTexture(Texture);
}
