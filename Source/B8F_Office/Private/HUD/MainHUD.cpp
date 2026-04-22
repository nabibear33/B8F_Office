// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainHUD.h"
#include "Components/DialogueComponent.h"
#include "Widgets/DialogueWidget.h"
#include "Widgets/LeftTimeWidget.h"
#include "GameInstances/EventBusSubsystem.h"
#include "Controllers/MainCharacterController.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    if (DialogueWidgetClass)
    {
        DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidget)
        {
            DialogueWidget->AddToViewport();
            DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (LeftTimeWidgetClass)
    {
        LeftTimeWidget = CreateWidget<ULeftTimeWidget>(GetWorld(), LeftTimeWidgetClass);
        if (LeftTimeWidget)
        {
            LeftTimeWidget->AddToViewport();
            LeftTimeWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    UEventBusSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEventBusSubsystem>();
    if (Subsystem)
    {
        Subsystem->OnLeftTimeUpdated.AddDynamic(LeftTimeWidget, &ULeftTimeWidget::OnLeftTimeUpdated);
    }

	// call OnDialogueWidgetReady to bind delegate in controller after widget is created
    if (AMainCharacterController* Controller = Cast<AMainCharacterController>(GetOwningPlayerController()))
    {
        Controller->OnDialogueWidgetReady();
	}
}

void AMainHUD::ShowDialogueWidget()
{
    if (!DialogueWidget) return;
    DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainHUD::HideDialogueWidget()
{
	if (!DialogueWidget) return;
	DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainHUD::ShowLeftTimeWidget()
{
    if (!LeftTimeWidget) return;
    LeftTimeWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainHUD::HideLeftTimeWidget()
{
    if (!LeftTimeWidget) return;
    LeftTimeWidget->SetVisibility(ESlateVisibility::Hidden);
}
