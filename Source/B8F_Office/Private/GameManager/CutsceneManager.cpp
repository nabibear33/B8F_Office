

#include "GameManager/CutsceneManager.h"
#include "LevelSequenceActor.h"
#include "DataTables/CutsceneRow.h"
#include "LevelSequencePlayer.h"
#include "GameInstances/MainGameInstance.h"
#include "GameInstances/GameSubsystem.h"

ACutsceneManager::ACutsceneManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACutsceneManager::BeginPlay()
{
	Super::BeginPlay();

	UGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (Subsystem)
	{
		Subsystem->SetCutsceneManager(this);
		OnGamePhaseUpdated.AddDynamic(Subsystem, &UGameSubsystem::OnGamePhaseUpdated);
		OnGameProgressEnded.AddDynamic(Subsystem, &UGameSubsystem::OnGameProgressEnded);
	}
}

void ACutsceneManager::OnCutsceneFinished()
{
	if (CurrentPlayingRow->CutsceneType == ECutsceneType::ECT_Death)
	{
		OnPlayerRevive.Broadcast();
	}

	CurrentPlayingRow = nullptr;
	OnGamePhaseUpdated.Broadcast(EGamePhase::EGP_Normal);
	OnGameProgressEnded.Broadcast();
}

void ACutsceneManager::PlayCutscene(FName RowName)
{
	OnGamePhaseUpdated.Broadcast(EGamePhase::EGP_CutScene);

	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (!GameInstance) return;
	
	CurrentPlayingRow = GameInstance->CutsceneDataTable->FindRow<FCutsceneRow>(RowName, TEXT(""));
	if (CurrentPlayingRow)
	{
		FMovieSceneSequencePlaybackSettings Settings;
		ALevelSequenceActor* TempActor = nullptr;
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			CurrentPlayingRow->LevelSequence,
			Settings,
			TempActor
		);
		LevelSequenceActor = TempActor;

		if (CurrentPlayingRow->CutsceneType == ECutsceneType::ECT_Death)
		{
			OnPlayerDeath.Broadcast();
		}

		LevelSequencePlayer->OnFinished.AddDynamic(this, &ACutsceneManager::OnCutsceneFinished);
		LevelSequencePlayer->Play();
	}

}

void ACutsceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

