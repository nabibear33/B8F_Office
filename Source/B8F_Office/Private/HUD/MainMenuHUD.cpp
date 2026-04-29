// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "Widgets/MainMenu/MainMenu.h"
#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "Widgets/MainMenu/StartGameWidget.h"
#include "Widgets/MainMenu/BackWidget.h"
#include "Controllers/MainMenuController.h"
#include "Widgets/MainMenu/CollectedAnomalyDetail.h"

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

    if (CollectionDetailWidgetClass)
    {
        CollectionDetailWidget = CreateWidget<UCollectedAnomalyDetail>(PC, CollectionDetailWidgetClass);
        if (CollectionDetailWidget)
        {
            CollectionDetailWidget->AddToViewport();
            CollectionDetailWidget->SetVisibility(ESlateVisibility::Hidden);
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
        MainMenuWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
        CollectionWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
    else
    {
        CollectionWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::EnableCollectionDetailWidget(bool Enabled)
{
    if (Enabled)
    {
        CollectionDetailWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
    else
    {
        CollectionDetailWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::EnableStartGameWidget(bool Enabled)
{
    if (Enabled)
    {
        StartGameWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
        BackWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
    EnableCollectionDetailWidget(false);
    EnableBackWidget(false);
}



void AMainMenuHUD::OnFinishedIntroCredit()
{
    EnableMainMenuWidget(true);
}

void AMainMenuHUD::OnCollectionDetailUpdated(FText AnomalyName, UTexture2D* Texture, FText AnomalyDetail)
{
    CollectionDetailWidget->AnomalyDetailUpdated(AnomalyName, Texture, AnomalyDetail);
}

void AMainMenuHUD::OnMainMenuStatusUpdated(EMainMenuStatus Status)
{
    DisableAllWidgets();

    if (Status == EMainMenuStatus::EMMS_MainMenu) EnableMainMenuWidget(true);
    if (Status == EMainMenuStatus::EMMS_StartGame) EnableStartGameWidget(true);
    if (Status == EMainMenuStatus::EMMS_Collection) EnableCollectionWidget(true);
    if (Status == EMainMenuStatus::EMMS_CollectionDetail) EnableCollectionDetailWidget(true);
    if (Status == EMainMenuStatus::EMMS_Setting) {}
    
    if (Status == EMainMenuStatus::EMMS_StartGame
        || Status == EMainMenuStatus::EMMS_Collection
        || Status == EMainMenuStatus::EMMS_Setting
        || Status == EMainMenuStatus::EMMS_CollectionDetail)
    {
        EnableBackWidget(true);
    }
}