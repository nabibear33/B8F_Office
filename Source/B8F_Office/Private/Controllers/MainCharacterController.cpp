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
#include "GameInstances/GameSubsystem.h"
#include "Widgets/MonologueWidget.h"

AMainCharacterController::AMainCharacterController()
{
    DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
}

void AMainCharacterController::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(IMC_Default, 0);
    }

    DialogueComponent->Initialize();

    UGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
    if (Subsystem)
    {
        Subsystem->SetPlayerController(this);
    }
}

void AMainCharacterController::OnDialogueWidgetReady()
{
    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (DialogueComponent && HUD)
    {
        DialogueComponent->OnDialogueUpdated.AddDynamic(HUD->GetDialogueWidget(), &UDialogueWidget::OnDialogueUpdated);
        DialogueComponent->OnDialogueUpdated.AddDynamic(HUD->GetMonologueWidget(), &UMonologueWidget::OnDialogueUpdated);
        DialogueComponent->OnCurrentHighlightedChoiceUpdated.AddDynamic(HUD->GetDialogueWidget()->GetChoiceList(), &UChoiceList::OnCurrentHighlightedChoiceUpdated);
        DialogueComponent->OnDialogueEnded.AddDynamic(this, &AMainCharacterController::EndDialogue);
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
    if (!bOnDialogue) return;
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

void AMainCharacterController::StartDialogue(UDataTable* DialogueDataTable, FName ID, EDialogueMode Mode)
{
    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (HUD)
    {
        switch (Mode)
        {
            case EDialogueMode::EDM_Dialogue:
                HUD->ShowDialogueWidget();
                break;
            case EDialogueMode::EDM_Monologue:
                HUD->ShowMonologueWidget();
                break;
            default:
                return;
        }
    }

    DialogueMode = Mode;
    bOnDialogue = true;
    DialogueComponent->StartDialogue(DialogueDataTable, ID);
}


void AMainCharacterController::OnGamePhaseUpdated(EGamePhase Phase)
{
    UE_LOG(LogTemp, Warning, TEXT("[AMainCharacterController] Set IMC"));
    switch (Phase)
    {
        case EGamePhase::EGP_Dialogue:
        case EGamePhase::EGP_Monologue:
            SetDialogueIMC();
            break;
        default:
            SetDefaultIMC();
            break;
    }
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

void AMainCharacterController::EndDialogue(FName DialogueID)
{
    // disable temporaly (later fully migrate to HUD)
    //DialogueTarget->GetInteractComponent()->SetInteractEnabled();
    //DialogueTarget = nullptr;

    AMainHUD* HUD = Cast<AMainHUD>(GetHUD());
    if (HUD)
    {
        switch (DialogueMode)
        {
            case EDialogueMode::EDM_Dialogue:
                HUD->HideDialogueWidget();
		        HUD->GetDialogueWidget()->ResetDialogueWidget();
                break;
            case EDialogueMode::EDM_Monologue:
                HUD->HideMonologueWidget();
		        HUD->GetMonologueWidget()->ResetMonologueWidget();
                break;
            default:
                return;
        }
    }
    
    bOnDialogue = false;
    DialogueMode = EDialogueMode::EDM_NotOnDialogue;

}