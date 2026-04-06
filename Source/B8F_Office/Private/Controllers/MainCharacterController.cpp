// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Interactable.h"
#include "HUD/MainHUD.h"


void AMainCharacterController::BeginPlay()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}

void AMainCharacterController::SetControlRotation(const FRotator& NewRotation)
{
    Super::SetControlRotation(NewRotation);
}