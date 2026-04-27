// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/BackWidget.h"
#include "Components/Button.h"
#include "Controllers/MainMenuController.h"

void UBackWidget::NativeConstruct()
{
	Super::NativeConstruct();

    AMainMenuController* PC = Cast<AMainMenuController>(GetOwningPlayer());
    if (PC)
    {
        BackButton->OnClicked.AddDynamic(PC, &AMainMenuController::OnClickedBack);
    }
}
