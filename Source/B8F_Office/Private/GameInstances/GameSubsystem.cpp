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
			UE_LOG(LogTemp, Warning, TEXT("[GameSubsystem] Update State to \"%s\""), *Name.ToString());
			CurrentProgressName = Name;
			CurrentGamePhase = Row->GamePhase;
			if (Row->NextProgressID != NAME_None)
			{
				WaitingProgressQueue.Enqueue(Row->NextProgressID);
			}
			ExecuteCurrentProgress(Row);
			SaveCurrentProgress();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[GameSubsystem] Row not found, which is named \"%s\""), *Name.ToString());
		}
	}
}

void UGameSubsystem::OnGamePhaseUpdated(EGamePhase Phase)
{
	CurrentGamePhase = Phase;
}

void UGameSubsystem::OnGameProgressEnded()
{
	// Triggered after finishing the dialogue or cutscene
	if (!WaitingProgressQueue.IsEmpty())
	{
		FName NextProgress;
		WaitingProgressQueue.Dequeue(NextProgress);
		OnGameProgressUpdated(NextProgress);
	}
}

void UGameSubsystem::SaveCurrentProgress()
{
	USaveSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	if (Subsystem)
	{
		UMainSaveGame* SaveGame = Subsystem->GetSaveGame();
		if (SaveGame)
		{
			SaveGame->SetProgressName(CurrentProgressName);
		}
		Subsystem->SaveGame();
	}
	
}

void UGameSubsystem::ExecuteCurrentProgress(FGameProgressRow* Row)
{
	ExecuteLevel(Row);

	FTimerHandle TempHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TempHandle,
		[this, Row]()
		{
			ExecuteGamePhase(Row);
		},
		0.2f,
		false);
}

void UGameSubsystem::ExecuteGamePhase(FGameProgressRow* Row)
{
	switch (Row->GamePhase)
	{
	case EGamePhase::EGP_Dialogue:
		PlayerController = Cast<AMainCharacterController>(
			UGameplayStatics::GetActorOfClass(this, AMainCharacterController::StaticClass()));
		PlayerController->StartDialogue(Row->DialogueDataTable, Row->DialogueRowName, EDialogueMode::EDM_Dialogue);
		break;
	case EGamePhase::EGP_Monologue:
		PlayerController = Cast<AMainCharacterController>(
			UGameplayStatics::GetActorOfClass(this, AMainCharacterController::StaticClass()));
		PlayerController->StartDialogue(Row->DialogueDataTable, Row->DialogueRowName, EDialogueMode::EDM_Monologue);
		break;
	case EGamePhase::EGP_CutScene:
		CutsceneManager = Cast<ACutsceneManager>(
			UGameplayStatics::GetActorOfClass(this, ACutsceneManager::StaticClass()));
		CutsceneManager->PlayCutscene(Row->CutsceneName);
		break;
	case EGamePhase::EGP_PlayMedia:
		// Get Media manager and play media (later)
		break;
	case EGamePhase::EGP_Normal:
		// Do Nothing
		break;
	}
}

void UGameSubsystem::ExecuteLevel(FGameProgressRow* Row)
{
	if (Row->LevelName != UGameplayStatics::GetCurrentLevelName(this, true))
	{
		UGameplayStatics::OpenLevel(this, Row->LevelName);
		CurrentLevel = Row->LevelName;
	}
}

void UGameSubsystem::UpdateManagers()
{
	CutsceneManager = Cast<ACutsceneManager>(
		UGameplayStatics::GetActorOfClass(this, ACutsceneManager::StaticClass()));
	
	PlayerController = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
}
