// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "Widgets/MainMenu.h"
#include "Widgets/CollectedAnomalyList.h"
#include "Controllers/MainMenuController.h"

void AMainMenuHUD::BeginPlay()
{
    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayerController());

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UMainMenu>(PC, MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();
            MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (CollectedAnomalyWidgetClass)
    {
        CollectedAnomalyWidget = CreateWidget<UCollectedAnomalyList>(PC, CollectedAnomalyWidgetClass);
        if (CollectedAnomalyWidget)
        {
            CollectedAnomalyWidget->AddToViewport();
            CollectedAnomalyWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    // Temp widget showing
    //ShowMainMenuWidget();
}

void AMainMenuHUD::ShowMainMenuWidget()
{
    MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuHUD::HideMainMenuWidget()
{
    MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHUD::OnFinishedIntroCredit()
{
    ShowMainMenuWidget();
}