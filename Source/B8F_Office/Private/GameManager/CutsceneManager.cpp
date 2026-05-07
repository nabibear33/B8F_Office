

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

void ACutsceneManager::OnCutsceneFinished()
{
	OnPlayerDeathAndReset.Broadcast();
}

void ACutsceneManager::PlayCutscene(FName RowName)
{
	FCutsceneRow* Row = CutsceneDataTable->FindRow<FCutsceneRow>(RowName, TEXT(""));
	if (Row)
	{
		ECutsceneType Type = Row->
	}

	if (Type == ECutsceneType::ECT_Death)
	{
		LevelSequencePlayer->OnFinished.AddDynamic(this, &ACutsceneManager::OnCutsceneFinished);
	}
	LevelSequencePlayer->Play();
}

void ACutsceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

