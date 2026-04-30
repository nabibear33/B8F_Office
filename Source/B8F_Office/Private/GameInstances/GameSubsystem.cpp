// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/GameSubsystem.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"

void UGameSubsystem::SetCurrentProgress(FName Name, EProgressType Type)
{
	CurrentProgressName = Name;
	CurrentProgressType = Type;

	USaveSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	UMainSaveGame* SaveGame = Subsystem->GetSaveGame();

	if (SaveGame)
	{
		SaveGame->SetProgressName(Name);
		Subsystem->SaveGame();
	}
}
