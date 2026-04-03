

#include "GameManager/CutsceneManager.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

ACutsceneManager::ACutsceneManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACutsceneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACutsceneManager::OnCutsceneFinished()
{
	OnPlayerDeathAndReset.Broadcast();
}

void ACutsceneManager::PlayDeathScene(EDeathSceneType DeathSceneType)
{
	ULevelSequencePlayer* LevelSequencePlayer = DeathScenes[DeathSceneType]->GetSequencePlayer();
	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->OnFinished.RemoveDynamic(this, &ACutsceneManager::OnCutsceneFinished);
		LevelSequencePlayer->OnFinished.AddDynamic(this, &ACutsceneManager::OnCutsceneFinished);
		UE_LOG(LogTemp, Warning, TEXT("Play DeathScene"));
		LevelSequencePlayer->Play();
	}
}

void ACutsceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

