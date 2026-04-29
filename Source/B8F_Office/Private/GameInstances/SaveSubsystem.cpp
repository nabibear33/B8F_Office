// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadGame();
}

void USaveSubsystem::SaveGame()
{
	if (!CurrentSaveGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGame: No CurrentSaveGame"));
		return;
	}

	bool bSuccess = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, UserIndex);
	UE_LOG(LogTemp, Warning, TEXT("SaveGame: %s"), bSuccess ? TEXT("Success") : TEXT("Failed"));
}

void USaveSubsystem::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CurrentSaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

		if (!CurrentSaveGame)
		{
			UE_LOG(LogTemp, Warning, TEXT("LoadGame: Casting Failed, Create New Save Game"));
			CreateNewSaveGame();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("LoadGame: Success"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadGame: No Save File, Create New Save Game"));
		CreateNewSaveGame();
	}
}

void USaveSubsystem::CreateNewSaveGame()
{
	CurrentSaveGame = Cast<UMainSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass())
	);

	CurrentSaveGame->InitializeAnomalyRecord();
	CurrentSaveGame->SetCurrentFloor(-8);

	SaveGame();
}
