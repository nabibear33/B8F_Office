// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/StartGameWidget.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Components/Button.h"
#include "Controllers/MainMenuController.h"


void UStartGameWidget::NativeConstruct()
{
    Super::NativeConstruct();

    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayer());
    if (PC)
    {
        NewGameButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedNewGame);
        ContinueButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedContinue);
        CollectionModeButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedCollectionMode);
        MarathonModeButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedMarathonMode);
    }

	USaveSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	UMainSaveGame* SaveGame = Subsystem->GetSaveGame();
	if (!(SaveGame->HasPlayedBefore()))
	{
		ContinueButton->SetIsEnabled(false);
	}
    if (!(SaveGame->IsNormalStageCleared()))
    {
        CollectionModeButton->SetIsEnabled(false);
        MarathonModeButton->SetIsEnabled(false);
    }
}
