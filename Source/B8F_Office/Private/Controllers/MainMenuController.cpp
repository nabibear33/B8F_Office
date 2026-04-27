// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainMenuController.h"
#include "HUD/MainMenuHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Save/MainSaveGame.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(true);
}

void AMainMenuController::OnClickedStartGame()
{
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_StartGame);
}

void AMainMenuController::OnClickedNewGame()
{
	UE_LOG(LogTemp, Warning, TEXT("New Game Button Clicked"));
	// open confirmation popup later

	// after given response from the confirmation popup
	USaveGameInstanceSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
	SaveSubsystem->CreateNewSaveGame();
	UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
	SaveGame->FirstPlay();
	UGameplayStatics::OpenLevel(this, FName("MainStage"));
}

void AMainMenuController::OnClickedContinue()
{
	UGameplayStatics::OpenLevel(this, FName("MainStage"));
}

void AMainMenuController::OnClickedCollectionMode()
{
	// start game with collection mode
}

void AMainMenuController::OnClickedMarathonMode()
{
	// Start Game with Marathon mode
}

void AMainMenuController::OnClickedCollection()
{
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_Collection);
}

void AMainMenuController::OnClickedSetting()
{
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_Setting);
}

void AMainMenuController::OnClickedQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void AMainMenuController::OnClickedBack()
{
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_MainMenu);
}

