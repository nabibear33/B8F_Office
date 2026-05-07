

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
		ECutsceneType Type = Row->CutsceneType;
		if (Type == ECutsceneType::ECT_Death)
		{
			OnPlayerDeath.Broadcast();
			Row->LevelSequencePlayer->OnFinished.AddDynamic(this, &ACutsceneManager::OnDeathsceneFinished);
		}
		Row->LevelSequencePlayer->Play();
	}

}

void ACutsceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

