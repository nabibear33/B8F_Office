

#include "GameManager/CutsceneManager.h"
#include "LevelSequenceActor.h"
#include "DataTables/CutsceneRow.h"
#include "LevelSequencePlayer.h"

ACutsceneManager::ACutsceneManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACutsceneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACutsceneManager::OnDeathsceneFinished()
{
	OnPlayerRevive.Broadcast();
}

void ACutsceneManager::PlayCutscene(FName RowName)
{
	FCutsceneRow* Row = CutsceneDataTable->FindRow<FCutsceneRow>(RowName, TEXT(""));
	if (Row)
	{
		FMovieSceneSequencePlaybackSettings Settings;
		ALevelSequenceActor* TempActor = nullptr;
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			Row->LevelSequence,
			Settings,
			TempActor
		);
		LevelSequenceActor = TempActor;

		ECutsceneType Type = Row->CutsceneType;
		if (Type == ECutsceneType::ECT_Death)
		{
			OnPlayerDeath.Broadcast();
			LevelSequencePlayer->OnFinished.AddDynamic(this, &ACutsceneManager::OnDeathsceneFinished);
		}
		LevelSequencePlayer->Play();
	}

}

void ACutsceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

