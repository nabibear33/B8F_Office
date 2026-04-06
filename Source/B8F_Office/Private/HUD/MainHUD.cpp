// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainHUD.h"
#include "Components/DialogueComponent.h"
#include "Widgets/DialogueWidget.h"

void AMainHUD::ShowDialogueWidget(UDialogueComponent* DialogueComponent)
{
	if (!DialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetOwningPlayerController());
	}

	DialogueComponent->OnDialogueUpdated.RemoveDynamic(DialogueWidget, &UDialogueWidget::OnDialogueUpdated);
	DialogueComponent->OnDialogueUpdated.AddDynamic(DialogueWidget, &UDialogueWidget::OnDialogueUpdated);

	DialogueWidget->AddToViewport();
}

void AMainHUD::HideDialogueWidget()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
	}
}
