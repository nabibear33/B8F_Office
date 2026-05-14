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
#include "Characters/MainCharacter.h"

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

    if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        EnhancedInputSubsystem->AddMappingContext(IMC_Default, 0);
        EnhancedInputSubsystem->AddMappingContext(IMC_Pause, 1);
    }

    DialogueComponent->Initialize();

    UGameSubsystem* GameSubsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
    if (GameSubsystem)
    {
        GameSubsystem->SetPlayerController(this);
        OnGameProgressUpdated.AddDynamic(GameSubsystem, &UGameSubsystem::OnGameProgressUpdated);
    }

    AMainCharacter* MainPlayer = Cast<AMainCharacter>(GetPawn());
    if (MainPlayer)
    {
        MainPlayer->OnCharacterStateUpdated.AddDynamic(this, &AMainCharacterController::OnCharacterStateUpdated);
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
        EIC->BindAction(IA_Pause, ETriggerEvent::Triggered, this,
            &AMainCharacterController::OnPauseButtonClicked);
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

EPauseStatus AMainCharacterController::GetParentStatus(EPauseStatus Status)
{
    switch (Status)
    {
        case EPauseStatus::EPS_Setting:
        case EPauseStatus::EPS_Collection:
            return EPauseStatus::EPS_PausedMain;
        case EPauseStatus::EPS_PausedMain:
        case EPauseStatus::EPS_NotPaused:
            return EPauseStatus::EPS_NotPaused;
        default:
            return EPauseStatus::EPS_PausedMain;
    }
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

void AMainCharacterController::OnCharacterStateUpdated(ECharacterState State)
{
    switch (State)
    {
        case ECharacterState::ECS_Sit:
        case ECharacterState::ECS_Dead:
            UE_LOG(LogTemp, Warning, TEXT("[MainCharacter Controller] Disable Player input"));
            SetIgnoreLookInput(true);
            SetIgnoreMoveInput(true);
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("[MainCharacter Controller] Enable Player input"));
            ResetIgnoreLookInput();
            ResetIgnoreMoveInput();
            break;
    }
}

void AMainCharacterController::OnResumeButtonClicked()
{
    Resume();
}

void AMainCharacterController::OnCollectionButtonClicked()
{
    CurrentPauseStatus = EPauseStatus::EPS_Collection;
    OnPauseStatusUpdated.Broadcast(EPauseStatus::EPS_Collection);
}

void AMainCharacterController::OnSettingButtonClicked()
{
    CurrentPauseStatus = EPauseStatus::EPS_Setting;
    OnPauseStatusUpdated.Broadcast(EPauseStatus::EPS_Setting);
}

void AMainCharacterController::OnMainMenuButtonClicked()
{
    UGameplayStatics::OpenLevel(this, FName(TEXT("MainMenu")));
}

void AMainCharacterController::OnPauseButtonClicked()
{
    switch (CurrentPauseStatus)
    {
        case EPauseStatus::EPS_NotPaused:
            Pause();
            break;
        case EPauseStatus::EPS_PausedMain:
            Resume();
            break;
        default:
            CurrentPauseStatus = GetParentStatus(CurrentPauseStatus);
            OnPauseStatusUpdated.Broadcast(CurrentPauseStatus);
            break;
    }
   
}

void AMainCharacterController::Pause()
{
    CurrentPauseStatus = EPauseStatus::EPS_PausedMain;
    UGameplayStatics::SetGamePaused(GetWorld(), true);

    FInputModeGameAndUI InputMode;
    SetInputMode(InputMode);
    bShowMouseCursor = true;

    OnPauseStatusUpdated.Broadcast(EPauseStatus::EPS_PausedMain);
}

void AMainCharacterController::Resume()
{
    CurrentPauseStatus = EPauseStatus::EPS_NotPaused;
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    bShowMouseCursor = false;

    OnPauseStatusUpdated.Broadcast(EPauseStatus::EPS_NotPaused);
}

void AMainCharacterController::OnClickedBack()
{
    CurrentPauseStatus = GetParentStatus(CurrentPauseStatus);
    OnPauseStatusUpdated.Broadcast(CurrentPauseStatus);
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