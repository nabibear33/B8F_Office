// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DialogueWidget.h"
#include "Components/TextBlock.h"

void UDialogueWidget::OnDialogueUpdated(const FDialogueRow& Row)
{
	DialogueText->SetText(Row.DialogueText);
	SpeakerIDText->SetText(FText::FromName(Row.SpeakerID));
}
