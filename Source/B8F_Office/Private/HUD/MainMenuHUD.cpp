// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "Widgets/MainMenu/MainMenu.h"
#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "Widgets/MainMenu/StartGameWidget.h"
#include "Widgets/MainMenu/BackWidget.h"
#include "Controllers/MainMenuController.h"

void AMainMenuHUD::BeginPlay()
{
    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayerController());
    if (PC)
    {
        PC->OnMainMenuStatusUpdated.AddDynamic(this, &AMainMenuHUD::OnMainMenuStatusUpdated);
    }

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UMainMenu>(PC, MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();
            MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (CollectionWidgetClass)
    {
        CollectionWidget = CreateWidget<UCollectedAnomalyList>(PC, CollectionWidgetClass);
        if (CollectionWidget)
        {
            CollectionWidget->AddToViewport();
            CollectionWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (StartGameWidgetClass)
    {
        StartGameWidget = CreateWidget<UStartGameWidget>(PC, StartGameWidgetClass);
        if (StartGameWidget)
        {
            StartGameWidget->AddToViewport();
            StartGameWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (BackWidgetClass)
    {
        BackWidget = CreateWidget<UBackWidget>(PC, BackWidgetClass);
        if (BackWidget)
        {
            BackWidget->AddToViewport();
            BackWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    // Temporarily widget showing
    EnableMainMenuWidget(true);
}

void AMainMenuHUD::EnableMainMenuWidget(bool Enabled)
{
    if (Enabled)
    {
        MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::EnableCollectionWidget(bool Enabled)
{
    if (Enabled)
    {
        CollectionWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        CollectionWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::EnableStartGameWidget(bool Enabled)
{
    if (Enabled)
    {
        StartGameWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        StartGameWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::EnableBackWidget(bool Enabled)
{
    if (Enabled)
    {
        BackWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        BackWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::DisableAllWidgets()
{
    EnableMainMenuWidget(false);
    EnableStartGameWidget(false);
    EnableCollectionWidget(false);
    EnableBackWidget(false);
}



void AMainMenuHUD::OnFinishedIntroCredit()
{
    EnableMainMenuWidget(true);
}

void AMainMenuHUD::OnMainMenuStatusUpdated(EMainMenuStatus Status)
{
    DisableAllWidgets();

    if (Status == EMainMenuStatus::EMMS_MainMenu) EnableMainMenuWidget(true);
    if (Status == EMainMenuStatus::EMMS_StartGame) EnableStartGameWidget(true);
    if (Status == EMainMenuStatus::EMMS_Collection) EnableCollectionWidget(true);
    if (Status == EMainMenuStatus::EMMS_Setting) {}
    
    if (Status == EMainMenuStatus::EMMS_StartGame
        || Status == EMainMenuStatus::EMMS_Collection
        || Status == EMainMenuStatus::EMMS_Setting)
    {
        EnableBackWidget(true);
    }
}