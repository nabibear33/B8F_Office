// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainHUD.h"
#include "Components/DialogueComponent.h"
#include "Widgets/MonologueWidget.h"
#include "Widgets/DialogueWidget.h"
#include "Widgets/LeftTimeWidget.h"
#include "GameInstances/EventBusSubsystem.h"
#include "Controllers/MainCharacterController.h"
#include "Widgets/InteractWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/PauseWidget.h"
#include "Widgets/MainMenu/CollectedAnomalyList.h"
#include "Widgets/OptionWidget.h"
#include "Widgets/MainMenu/BackWidget.h"


void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    AMainCharacterController* PC = Cast<AMainCharacterController>(GetOwningPlayerController());
    if (PC)
    {
        PC->OnPauseStatusUpdated.AddDynamic(this, &AMainHUD::OnPauseStatusUpdated);
        DialogueWidget = CreateWidgetFromWidgetClass<UDialogueWidget>(PC, DialogueWidgetClass);
        MonologueWidget = CreateWidgetFromWidgetClass<UMonologueWidget>(PC, MonologueWidgetClass);
        LeftTimeWidget = CreateWidgetFromWidgetClass<ULeftTimeWidget>(PC, LeftTimeWidgetClass);
        InteractWidget = CreateWidgetFromWidgetClass<UInteractWidget>(PC, InteractWidgetClass);
        PauseWidget = CreateWidgetFromWidgetClass<UPauseWidget>(PC, PauseWidgetClass);
        CollectionWidget = CreateWidgetFromWidgetClass<UCollectedAnomalyList>(PC, CollectionWidgetClass);
        SettingWidget = CreateWidgetFromWidgetClass<UOptionWidget>(PC, SettingWidgetClass);
        BackWidget = CreateWidgetFromWidgetClass<UBackWidget>(PC, BackWidgetClass);
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

void AMainHUD::DisableAllWidgets()
{

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

void AMainHUD::ShowMonologueWidget()
{
    if (!MonologueWidget) return;
    MonologueWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainHUD::HideMonologueWidget()
{
    if (!MonologueWidget) return;
    MonologueWidget->SetVisibility(ESlateVisibility::Hidden);
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

void AMainHUD::ShowInteractWidget()
{
    if (!InteractWidget) return;
    InteractWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainHUD::HideInteractWidget()
{
    if (!InteractWidget) return;
    InteractWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainHUD::OnInteractableUpdated(AActor* InteractableActor, FVector ActorLocation, FText InteractText)
{
    UE_LOG(LogTemp, Warning, TEXT("[Main HUD] Interactable : %s"), *InteractableActor->GetName());
    InteractWidget->SetInteractContentText(InteractText);
    ShowInteractWidget();
}

void AMainHUD::SetWidgetVisibility(UUserWidget* Widget, bool Enabled)
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

void AMainHUD::OnInteractableLeft(AActor* InteractableActor)
{
    InteractWidget->SetInteractContentText(FText::GetEmpty());
    HideInteractWidget();
}

void AMainHUD::OnGamePhaseUpdated(EGamePhase Phase)
{
    switch (Phase)
    {
        case EGamePhase::EGP_Normal:
            break;
        default:
            HideInteractWidget();
            break;
    }
}

void AMainHUD::OnPauseStatusUpdated(EPauseStatus Status)
{
    SetWidgetVisibility(PauseWidget, false);
    SetWidgetVisibility(CollectionWidget, false);
    SetWidgetVisibility(SettingWidget, false);
    SetWidgetVisibility(BackWidget, false);

    switch (Status)
    {
        case EPauseStatus::EPS_PausedMain:
            SetWidgetVisibility(PauseWidget, true);
            break;
        case EPauseStatus::EPS_Collection:
            SetWidgetVisibility(CollectionWidget, true);
            break;
        case EPauseStatus::EPS_Setting:
            SetWidgetVisibility(SettingWidget, true);
            break;
        default:
            break;
    }

    switch (Status)
    {
        case EPauseStatus::EPS_PausedMain:
        case EPauseStatus::EPS_NotPaused:
            break;
        default:
            SetWidgetVisibility(BackWidget, true);
            break;
    }
}
