// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Interactable.h"
#include "DataTables/DialogueRow.h"
#include "HUD/MainHUD.h"
#include "EnhancedInputSubsystems.h"
#include "Components/DialogueComponent.h"
#include "Widgets/DialogueWidget.h"
#include "Widgets/ChoiceList.h"
#include "Characters/InteractableCharacter.h"
#include "Components/InteractComponent.h"
#include "EnhancedInputComponent.h"

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


    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(IMC_Default, 0);
    }

}

void AMainCharacterController::OnDialogueWidgetReady()
{
    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (DialogueComponent && HUD)
    {
        DialogueComponent->OnDialogueUpdated.AddDynamic(HUD->GetDialogueWidget(), &UDialogueWidget::OnDialogueUpdated);
        DialogueComponent->OnCurrentHighlightedChoiceUpdated.AddDynamic(HUD->GetDialogueWidget()->GetChoiceList(), &UChoiceList::OnCurrentHighlightedChoiceUpdated);
    }
}

void AMainCharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EIC->BindAction(IA_AdvanceDialogue, ETriggerEvent::Triggered, this,
            &AMainCharacterController::OnAdvanceDialogue);
        EIC->BindAction(IA_NavigateChoice, ETriggerEvent::Triggered, this,
            &AMainCharacterController::OnNavigateChoice);
        EIC->BindAction(IA_SelectChoice, ETriggerEvent::Triggered, this,
            &AMainCharacterController::OnSelectChoice);
    }
}

void AMainCharacterController::OnAdvanceDialogue()
{
	DialogueComponent->AdvanceDialogue();
}

void AMainCharacterController::OnNavigateChoice(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();
	DialogueComponent->NavigateCurrentChoiceIdx(InputValue);
    
}

void AMainCharacterController::OnSelectChoice()
{
	UE_LOG(LogTemp, Warning, TEXT("Select Choice"));
	DialogueComponent->OnSelectCurrentChoice();
}


void AMainCharacterController::SetControlRotation(const FRotator& NewRotation)
{
    Super::SetControlRotation(NewRotation);
}

void AMainCharacterController::StartDialogue(AInteractableCharacter* DialogueTarget_, UDataTable* DialogueDataTable, FName ID)
{
    DialogueTarget = DialogueTarget_;

    SetDialogueIMC();

    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (HUD)
    {
        HUD->ShowDialogueWidget(DialogueComponent);
    }

    DialogueComponent->StartDialogue(DialogueDataTable, ID);

}

void AMainCharacterController::SetDialogueIMC()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        Subsystem->RemoveMappingContext(IMC_Default);
        Subsystem->AddMappingContext(IMC_Dialogue, 0);
    }
}

void AMainCharacterController::SetDefaultIMC()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        Subsystem->RemoveMappingContext(IMC_Dialogue);
        Subsystem->AddMappingContext(IMC_Default, 0);
    }
}

void AMainCharacterController::EndDialogue()
{

    DialogueTarget->GetInteractComponent()->SetInteractEnabled();
    DialogueTarget = nullptr;

    SetDefaultIMC();
    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (HUD)
    {
        HUD->HideDialogueWidget();
		HUD->GetDialogueWidget()->ResetDialogueWidget();
    }
}