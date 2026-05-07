// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/GameSubsystem.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/MainCharacterController.h"
#include "GameManager/CutsceneManager.h"

void UGameSubsystem::OnProgressUpdated(FName Name)
{
	if (ProgressDataTable)
	{
		FGameProgressRow* Row = ProgressDataTable->FindRow<FGameProgressRow>(Name, TEXT(""));

		if (Row)
		{
			CurrentProgressName = Name;
			CurrentProgressType = Row->ProgressType;
			CurrentLevel = Row->LevelName;
			ExecuteCurrentProgress(_placeholder_);
		}
	}
}

void UGameSubsystem::SaveCurrentProgress()
{
	USaveSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	UMainSaveGame* SaveGame = Subsystem->GetSaveGame();

	if (SaveGame)
	{
		SaveGame->SetProgressName(CurrentProgressName);
		Subsystem->SaveGame();
	}
}

void UGameSubsystem::ExecuteCurrentProgress(FGameProgressRow* Row)
{
	if (CurrentLevel != UGameplayStatics::GetCurrentLevelName(this, true))
	{
		UGameplayStatics::OpenLevel(this, CurrentLevel);
		UpdateManagers();
	}

	switch (CurrentProgressType)
	{
		case EProgressType::EPT_Dialogue:
			if (PC)
			{
				PC->StartDialogue(Row->DialogueRowName);
			}
			break;
		case EProgressType::EPT_CutScene:
			if (CutsceneManager)
			{
				CutsceneManager->
			}
			break;
		case EProgressType::EPT_PlayMedia:
			// Get Media manager and play media (later)
			break;
		case EProgressType::EPT_Normal:
			// Do Nothing
			break;
	}
}

void UGameSubsystem::UpdateManagers()
{
	CutsceneManager = Cast<ACutsceneManager>(
		UGameplayStatics::GetActorOfClass(this, ACutsceneManager::StaticClass()));
	
	PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
}

