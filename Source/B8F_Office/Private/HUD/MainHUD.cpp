// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainHUD.h"
#include "Components/DialogueComponent.h"
#include "Widgets/DialogueWidget.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    if (DialogueWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueWidgetClass Checked"));
        DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Initialize Dialogue Widget"));
            DialogueWidget->AddToViewport();
            DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void AMainHUD::ShowDialogueWidget(UDialogueComponent* DialogueComponent)
{
    if (!DialogueWidget || !DialogueComponent) return;

    UE_LOG(LogTemp, Warning, TEXT("Show Dialogue Widget"));
    DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainHUD::HideDialogueWidget()
{
	if (!DialogueWidget) return;

    UE_LOG(LogTemp, Warning, TEXT("Hide Dialogue Widget"));
	DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
}
