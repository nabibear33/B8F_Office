// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseWidget.h"
#include "Controllers/MainCharacterController.h"
#include "Components/Button.h"

void UPauseWidget::NativeConstruct()
{
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		ResumeButton->OnClicked.AddDynamic(PC, &AMainCharacterController::OnResumeButtonClicked);
		CollectionButton->OnClicked.AddDynamic(PC, &AMainCharacterController::OnCollectionButtonClicked);
		SettingButton->OnClicked.AddDynamic(PC, &AMainCharacterController::OnSettingButtonClicked);
		MainMenuButton->OnClicked.AddDynamic(PC, &AMainCharacterController::OnMainMenuButtonClicked);
	}
}
