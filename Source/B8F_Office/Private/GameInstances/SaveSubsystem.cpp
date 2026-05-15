// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/SaveSubsystem.h"
#include "GameInstances/GameSubsystem.h"
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
		UE_LOG(LogTemp, Warning, TEXT("[SaveSubsystem] SaveGame: No CurrentSaveGame"));
		return;
	}

	bool bSuccess = UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, UserIndex);
	UE_LOG(LogTemp, Warning, TEXT("[SaveSubsystem] SaveGame: %s"), bSuccess ? TEXT("Success") : TEXT("Failed"));
	if (bSuccess)
	{
		CurrentSaveGame->PrintSaveData();
	}
}

void USaveSubsystem::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CurrentSaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

		if (!CurrentSaveGame)
		{
			UE_LOG(LogTemp, Warning, TEXT("[SaveSubsystem] LoadGame: Casting Failed, Create New Save Game"));
			CreateNewSaveGame();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[SaveSubsystem] LoadGame: Success"));
			CurrentSaveGame->PrintSaveData();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[SaveSubsystem] LoadGame: No Save File, Create New Save Game"));
		CreateNewSaveGame();
	}
}

void USaveSubsystem::CreateNewSaveGame()
{
	CurrentSaveGame = Cast<UMainSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass())
	);
	CurrentSaveGame->SetProgressName(FName(TEXT("Room_Intro")));
	CurrentSaveGame->SetAllAnomalyUnSeen();
	CurrentSaveGame->SetMainStageFloor(-8);

	SaveGame();
}
