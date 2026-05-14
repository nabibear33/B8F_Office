// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "Widgets/MainMenu/MainMenu.h"
#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "Widgets/MainMenu/StartGameWidget.h"
#include "Widgets/MainMenu/BackWidget.h"
#include "Widgets/OptionWidget.h"
#include "Controllers/MainMenuController.h"
#include "Widgets/MainMenu/CollectedAnomalyDetail.h"

void AMainMenuHUD::BeginPlay()
{
    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayerController());
    if (PC)
    {
        PC->OnMainMenuStatusUpdated.AddDynamic(this, &AMainMenuHUD::OnMainMenuStatusUpdated);
        MainMenuWidget = CreateWidgetFromWidgetClass<UMainMenu>(PC, MainMenuWidgetClass);
        CollectionWidget = CreateWidgetFromWidgetClass<UCollectedAnomalyList>(PC, CollectionWidgetClass);
        CollectionDetailWidget = CreateWidgetFromWidgetClass<UCollectedAnomalyDetail>(PC, CollectionDetailWidgetClass);
        StartGameWidget = CreateWidgetFromWidgetClass<UStartGameWidget>(PC, StartGameWidgetClass);
        BackWidget = CreateWidgetFromWidgetClass<UBackWidget>(PC, BackWidgetClass);
        OptionWidget = CreateWidgetFromWidgetClass<UOptionWidget>(PC, OptionWidgetClass);
    }

    // Temporarily widget showing
    SetWidgetVisibility(MainMenuWidget, true);
}

void AMainMenuHUD::SetWidgetVisibility(UUserWidget* Widget, bool Enabled)
{
    if (Enabled)
    {
        Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
    else
    {
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainMenuHUD::DisableAllWidgets()
{
    SetWidgetVisibility(MainMenuWidget, false);
    SetWidgetVisibility(StartGameWidget, false);
    SetWidgetVisibility(CollectionWidget, false);
    SetWidgetVisibility(CollectionDetailWidget, false);
    SetWidgetVisibility(BackWidget, false);
    SetWidgetVisibility(OptionWidget, false);
}



void AMainMenuHUD::OnFinishedIntroCredit()
{
    SetWidgetVisibility(MainMenuWidget, true);
}

void AMainMenuHUD::OnCollectionDetailUpdated(FText AnomalyName, UTexture2D* Texture, FText AnomalyDetail)
{
    CollectionDetailWidget->AnomalyDetailUpdated(AnomalyName, Texture, AnomalyDetail);
}

void AMainMenuHUD::OnMainMenuStatusUpdated(EMainMenuStatus Status)
{
    DisableAllWidgets();

    if (Status == EMainMenuStatus::EMMS_MainMenu) SetWidgetVisibility(MainMenuWidget, true);
    if (Status == EMainMenuStatus::EMMS_StartGame) SetWidgetVisibility(StartGameWidget, true);
    if (Status == EMainMenuStatus::EMMS_Collection) SetWidgetVisibility(CollectionWidget, true);
    if (Status == EMainMenuStatus::EMMS_CollectionDetail) SetWidgetVisibility(CollectionDetailWidget, true);
    if (Status == EMainMenuStatus::EMMS_Setting) SetWidgetVisibility(OptionWidget, true);
    
    if (Status == EMainMenuStatus::EMMS_StartGame
        || Status == EMainMenuStatus::EMMS_Collection
        || Status == EMainMenuStatus::EMMS_Setting
        || Status == EMainMenuStatus::EMMS_CollectionDetail)
    {
        SetWidgetVisibility(BackWidget, true);
    }
}