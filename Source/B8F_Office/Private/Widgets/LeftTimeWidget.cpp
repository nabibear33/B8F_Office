// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LeftTimeWidget.h"
#include "Components/TextBlock.h"

void ULeftTimeWidget::OnLeftTimeUpdated(float Value)
{
    FText FormattedText = FText::FromString(
        FString::Printf(TEXT("Left Time : %.1f"), Value)
    );

    LeftTimeText->SetText(FormattedText);

}
