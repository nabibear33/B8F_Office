// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MonologueWidget.h"
#include "Components/TextBlock.h"

void UMonologueWidget::OnDialogueUpdated(const FDialogueRow& Row)
{
	MonologueText->SetText(Row.DialogueText);
}

void UMonologueWidget::ResetMonologueWidget()
{
	MonologueText->SetText(FText::GetEmpty());
}
