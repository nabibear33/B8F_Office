// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Save/MainSaveGame.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Controllers/MainMenuController.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayer());
    if (PC)
    {
        NewGameButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedNewGame);
        ContinueButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedContinue);
        CollectionButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedCollection);
        SettingButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedSetting);
        QuitButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedQuit);
    }

    SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
    SaveGame = SaveSubsystem->GetSaveGame();
    
    if (!SaveGame->HasPlayedBefore())
    {
        ContinueButton->SetIsEnabled(false);
    }
}

void UMainMenu::OnNewGameButtonClicked()
{
    SaveSubsystem->CreateNewSaveGame();
    SaveGame = SaveSubsystem->GetSaveGame();
    SaveGame->FirstPlay();
    UGameplayStatics::OpenLevel(this, FName("MainStage"));
}

void UMainMenu::OnContinueButtonClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainStage"));
}

void UMainMenu::OnQuitButtonClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UMainMenu::OnCollectionButtonClicked()
{

}

void UMainMenu::OnSettingButtonClicked()
{
}
