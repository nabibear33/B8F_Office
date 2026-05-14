// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Save/MainSaveGame.h"
#include "GameInstances/SaveSubsystem.h"
#include "Controllers/MainMenuController.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayer());
    if (PC)
    {
        StartGameButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedStartGame);
        CollectionButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedCollection);
        SettingButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedSetting);
        QuitButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedQuit);
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