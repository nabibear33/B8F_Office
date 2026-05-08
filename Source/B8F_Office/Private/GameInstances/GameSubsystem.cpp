// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/GameSubsystem.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/MainCharacterController.h"
#include "GameManager/CutsceneManager.h"
#include "GameInstances/MainGameInstance.h"

void UGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		ProgressDataTable = GameInstance->ProgressDataTable;
	}
}

void UGameSubsystem::OnGameProgressUpdated(FName Name)
{
	if (ProgressDataTable)
	{
		FGameProgressRow* Row = ProgressDataTable->FindRow<FGameProgressRow>(Name, TEXT(""));

		if (Row)
		{
			CurrentProgressName = Name;
			CurrentGamePhase = Row->GamePhase;
			CurrentLevel = Row->LevelName;
			ExecuteCurrentProgress(Row);
		}
	}
}

void UGameSubsystem::OnGamePhaseUpdated(EGamePhase Phase)
{
	CurrentGamePhase = Phase;
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
	}

	switch (CurrentGamePhase)
	{
		case EGamePhase::EGP_Dialogue:
			if (PlayerController)
			{
				PlayerController->StartDialogue(Row->DialogueDataTable, Row->DialogueRowName);
			}
			break;
		case EGamePhase::EGP_CutScene:
			if (CutsceneManager)
			{
				CutsceneManager->PlayCutscene(Row->CutsceneName);
			}
			else
			{
				CutsceneManager = Cast<ACutsceneManager>(
					UGameplayStatics::GetActorOfClass(this, ACutsceneManager::StaticClass()));
				UE_LOG(LogTemp, Warning, TEXT("No Cutscene Manager"));
				CutsceneManager->PlayCutscene(Row->CutsceneName);
			}
			break;
		case EGamePhase::EGP_PlayMedia:
			// Get Media manager and play media (later)
			break;
		case EGamePhase::EGP_Normal:
			// Do Nothing
			break;
	}
}

void UGameSubsystem::UpdateManagers()
{
	CutsceneManager = Cast<ACutsceneManager>(
		UGameplayStatics::GetActorOfClass(this, ACutsceneManager::StaticClass()));
	
	PlayerController = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
}

