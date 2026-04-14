// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Interactable.h"
#include "DataTables/DialogueRow.h"
#include "HUD/MainHUD.h"
#include "Components/DialogueComponent.h"

AMainCharacterController::AMainCharacterController()
{
    DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
}

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

void AMainCharacterController::StartDialogue(UDataTable* DialogueDataTable, FName ID)
{
    DialogueComponent->SetDialogueDataTable(DialogueDataTable);
    DialogueComponent->SetCurrentRowID(ID);
    DialogueComponent->StartDialogue();

    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (HUD)
    {
        HUD->ShowDialogueWidget(DialogueComponent);
    }
}
