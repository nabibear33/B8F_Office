

#include "GameManager/GameManager.h"
#include "GameManager/CutsceneManager.h"
#include "GameManager/StageManager.h"
#include "GameLogics/StageStartArea.h"
#include "GameLogics/TeleportArea.h"
#include "Characters/MainCharacter.h"
#include "Characters/NotKommy.h"
#include "GameLogics/NotKommyTriggerArea.h"
#include "GameLogics/Types.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Kismet/GameplayStatics.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

FVector AGameManager::GetPlayerLocation()
{
	return Player->GetActorLocation();
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
	SaveGame = SaveSubsystem->GetSaveGame();

	if (StageStartAreaUp && StageStartAreaDown && TeleportAreaUp && TeleportAreaDown)
	{
		StageStartAreaUp->OnAreaTriggered.AddDynamic(this, &AGameManager::OnStageStartAreaTriggered);
		StageStartAreaDown->OnAreaTriggered.AddDynamic(this, &AGameManager::OnStageStartAreaTriggered);
		TeleportAreaUp->OnAreaTriggered.AddDynamic(this, &AGameManager::OnTeleportAreaTriggered);
		TeleportAreaDown->OnAreaTriggered.AddDynamic(this, &AGameManager::OnTeleportAreaTriggered);
	}

	if (NotKommy)
	{
		NotKommy->OnPlayDeathScene.AddDynamic(this, &AGameManager::OnPlayDeathScene);
	}

	if (CutsceneManager)
	{
		CutsceneManager->OnPlayerDeathAndReset.AddDynamic(this, &AGameManager::OnPlayerDeathAndReset);
	}

	InitializeInfoPanel();
}

void AGameManager::OnStageStartAreaTriggered(AActor* TriggeringArea, AActor* OtherActor)
{
	StageStartAreaUp->DisableArea();
	StageStartAreaDown->DisableArea();

	TeleportAreaUp->EnableArea();
	TeleportAreaDown->EnableArea();

	if (bHasFirstEntered)
	{
		StageManager->SetNormalStage();
		bHasFirstEntered = false;
	}
	else
	{
		StageManager->ResetStage();
	}

	bool bRequiresDefeat = FAnomalyTypeHelper::RequiresDefeat(StageManager->GetAnomalyType());
	if (bRequiresDefeat)
	{
		// lock the door
		
	}

	Player->ResetInteractableCount();



	UE_LOG(LogTemp, Warning, TEXT("Now New Stage Start"));

	
}

void AGameManager::OnTeleportAreaTriggered(AActor* TriggeringArea, AActor* OtherActor)
{
	StageStartAreaUp->EnableArea();
	StageStartAreaDown->EnableArea();

	TeleportAreaUp->DisableArea();
	TeleportAreaDown->DisableArea();

	UE_LOG(LogTemp, Warning, TEXT("Choice Submitted"));

	ATeleportArea* TriggeringAreaCasted = Cast<ATeleportArea>(TriggeringArea);

	if (TriggeringAreaCasted)
	{
		HandlePlayerChoice(TriggeringAreaCasted);
	}
}

void AGameManager::OnPlayDeathScene(EDeathSceneType DeathSceneType)
{
	Player->OnDeath();

	CutsceneManager->PlayDeathScene(DeathSceneType);

}



void AGameManager::HandlePlayerChoice(ATeleportArea* AreaPlayerEntered)
{
	EStageState StageState = GetStageManager()->GetStageState();

	int32 NextFloor;

	if (IsCorrect(StageState, AreaPlayerEntered))
	{
		UE_LOG(LogTemp, Warning, TEXT("Correct Answer"));
		NextFloor = SaveGame->GetCurrentFloor() + 1;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Answer"));
		NextFloor = -8;
	}
	SaveGame->SetCurrentFloor(NextFloor);

	EAnomalyType AnomalyType = GetStageManager()->GetAnomalyType();
	EAnomalyStatus AnomalyStatus = GetStageManager()->GetAnomalyStatus();
	SaveGame->SetAnomalyRecord(AnomalyType, AnomalyStatus);

	SaveData();

	UpdateInfoPanel(NextFloor, AnomalyType, AnomalyStatus);

	// Add logics when Floor is 1F.
	if (NextFloor == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Win the Game"));
		SaveGame->NormalStageCleared();
		SaveData();
		// show lobby instead
		UGameplayStatics::OpenLevel(this, FName("MainMenu"));
	}

}

bool AGameManager::IsCorrect(EStageState StageState, ATeleportArea*& AreaPlayerEntered)
{
	return (StageState == EStageState::ESS_Normal && AreaPlayerEntered == TeleportAreaUp)
		|| (StageState == EStageState::ESS_Anomaly && AreaPlayerEntered == TeleportAreaDown);
}

void AGameManager::SaveData()
{
	if (SaveSubsystem)
	{
		SaveSubsystem->SaveGame();
		UE_LOG(LogTemp, Warning, TEXT("Saved Data"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Save Subsystem"));
	}
}


void AGameManager::InitializeInfoPanel()
{

}

void AGameManager::UpdateInfoPanel(int32 Floor, EAnomalyType AnomalyType, EAnomalyStatus AnomalyStatus)
{
	OnInfoPanelUpdated.Broadcast(Floor, AnomalyType, AnomalyStatus);
}

void AGameManager::OnPlayerDeathAndReset()
{
	EAnomalyType AnomalyType = GetStageManager()->GetAnomalyType();
	EAnomalyStatus AnomalyStatus = GetStageManager()->GetAnomalyStatus();
	UpdateInfoPanel(-8, AnomalyType, AnomalyStatus);
	StageManager->ResetStage();
	Player->OnRevive();
}

