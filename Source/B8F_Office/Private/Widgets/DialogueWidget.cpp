// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/ChoiceList.h"

void UDialogueWidget::OnDialogueUpdated(const FDialogueRow& Row)
{
	DialogueText->SetText(Row.DialogueText);
	SpeakerIDText->SetText(FText::FromName(Row.SpeakerID));
	if(!Row.Choices.IsEmpty())
	{
		ChoiceList->SetVisibility(ESlateVisibility::Visible);
		ChoiceList->SetChoiceItems(Row);
	}
	else
	{
		ChoiceList->SetVisibility(ESlateVisibility::Collapsed);
	}
}
