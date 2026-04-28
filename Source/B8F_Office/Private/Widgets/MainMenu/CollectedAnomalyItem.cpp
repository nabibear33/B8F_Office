// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu/CollectedAnomalyItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Controllers/MainMenuController.h"
#include "Components/Button.h"
#include "HUD/MainMenuHUD.h"

void UCollectedAnomalyItem::NativeConstruct()
{
	DetailButton->OnClicked.AddDynamic(this, &UCollectedAnomalyItem::OnClickedCollectionDetail);
	
	AMainMenuController* PC = Cast<AMainMenuController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		OnCollectionItemClicked.AddDynamic(PC, &AMainMenuController::OnClickedCollectionItem);
	}

}

void UCollectedAnomalyItem::SetAnomalyName(FText Text)
{
	CachedAnomalyName = Text;
	AnomalyName->SetText(Text);
}

void UCollectedAnomalyItem::SetAnomalyImage(UTexture2D* Texture)
{
	CachedAnomalyTexture = Texture;
	AnomalyImage->SetBrushFromTexture(Texture);
}

void UCollectedAnomalyItem::SetAnomalyDetail(FText Text)
{
	CachedAnomalyDetail = Text;
}

void UCollectedAnomalyItem::OnClickedCollectionDetail()
{

	OnCollectionItemClicked.Broadcast(CachedAnomalyName, CachedAnomalyTexture, CachedAnomalyDetail);
}
