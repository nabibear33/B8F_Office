// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainMenuController.h"
#include "HUD/MainMenuHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(true);
}

EMainMenuStatus AMainMenuController::GetParentStatus(EMainMenuStatus Status)
{
	switch (Status)
	{
		case EMainMenuStatus::EMMS_CollectionDetail:
			return EMainMenuStatus::EMMS_Collection;
		case EMainMenuStatus::EMMS_StartGame:
		case EMainMenuStatus::EMMS_Collection:
		case EMainMenuStatus::EMMS_Setting:
		default:
			return EMainMenuStatus::EMMS_MainMenu;
	}
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
	USaveSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	SaveSubsystem->CreateNewSaveGame();
	UMainSaveGame* SaveGame = SaveSubsystem->GetSaveGame();
	SaveGame->FirstPlay();
	UGameplayStatics::OpenLevel(this, NewGameLevelName);
}

void AMainMenuController::OnClickedContinue()
{
	UGameplayStatics::OpenLevel(this, NewGameLevelName);
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
	CurrentStatus = EMainMenuStatus::EMMS_Collection;
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_Collection);
}

void AMainMenuController::OnClickedCollectionItem(FText AnomalyName, UTexture2D* Texture, FText AnomalyDetail)
{
	CurrentStatus = EMainMenuStatus::EMMS_CollectionDetail;
	AMainMenuHUD* HUD = Cast<AMainMenuHUD>(GetHUD());
	HUD->OnCollectionDetailUpdated(AnomalyName, Texture, AnomalyDetail);
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_CollectionDetail);
}

void AMainMenuController::OnClickedSetting()
{
	CurrentStatus = EMainMenuStatus::EMMS_Setting;
	OnMainMenuStatusUpdated.Broadcast(EMainMenuStatus::EMMS_Setting);
}

void AMainMenuController::OnClickedQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void AMainMenuController::OnClickedBack()
{
	CurrentStatus = GetParentStatus(CurrentStatus);
	OnMainMenuStatusUpdated.Broadcast(CurrentStatus);
}

