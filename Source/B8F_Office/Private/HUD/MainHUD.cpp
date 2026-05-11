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

    if (MonologueWidgetClass)
    {
        MonologueWidget = CreateWidget<UMonologueWidget>(GetWorld(), MonologueWidgetClass);
        if (MonologueWidget)
        {
            MonologueWidget->AddToViewport();
            MonologueWidget->SetVisibility(ESlateVisibility::Hidden);
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

    if (InteractWidgetClass)
    {
        InteractWidget = CreateWidget<UInteractWidget>(GetWorld(), InteractWidgetClass);
        if (InteractWidget)
        {
            InteractWidget->AddToViewport();
            InteractWidget->SetVisibility(ESlateVisibility::Hidden);
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