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
}

void AMainMenuController::OnClickedStartGame()
{
	// open start game widget hierarchy (new game / continue) 
}

void AMainMenuController::OnClickedNewGame()
{
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

void AMainMenuController::OnClickedCollection()
{
	//open collection widget
}

void AMainMenuController::OnClickedSetting()
{
	// open setting widget
}

void AMainMenuController::OnClickedQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

