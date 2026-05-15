

#include "Widgets/InfoPanelWidget.h"
#include "GameManager/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "GameInstances/SaveSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Widgets/AnomalyStatusEntry.h"

void UInfoPanelWidget::PopulateFromRecord(const TArray<FAnomalyEntry>& AnomalyRecord)
{
	EntryContainer->ClearChildren();
	for (const FAnomalyEntry& Entry : AnomalyRecord)
	{
		if (Entry.Type == EAnomalyType::EAT_None || Entry.Type == EAnomalyType::EAT_MAX) continue;
		UAnomalyStatusEntry* Widget = CreateWidget<UAnomalyStatusEntry>(this, EntryWidget);
		if (!Widget)
		{
			UE_LOG(LogTemp, Error, TEXT("CreateWidget failed for Type: %s"), *UEnum::GetValueAsString(Entry.Type));
			continue;
		}
		Widget->UpdateEntry(Entry.Type, Entry.Status);
		EntryContainer->AddChild(Widget);
	}
}

void UInfoPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AGameManager* GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	if (GameManager)
	{
		GameManager->OnInfoPanelUpdated.AddDynamic(this, &UInfoPanelWidget::OnInfoPanelUpdated);
	}

	DrawCurrentFloor(GetGameInstance()->GetSubsystem<USaveSubsystem>()->GetSaveGame()->GetMainStageFloor());
	DrawAnomalyRecord();
}

void UInfoPanelWidget::DrawAnomalyRecord()
{
	USaveSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
	if (SaveSubsystem && SaveSubsystem->GetSaveGame())
	{
		PopulateFromRecord(SaveSubsystem->GetSaveGame()->GetAnomalyRecord());
	}
}

void UInfoPanelWidget::OnInfoPanelUpdated(int32 Floor, EAnomalyType AnomalyType, EAnomalyStatus AnomalyStatus)
{
	UE_LOG(LogTemp, Warning, TEXT("Info Panel Changed"));

	DrawCurrentFloor(Floor);

	DrawAnomalyRecord();
}

void UInfoPanelWidget::DrawCurrentFloor(int32 Floor)
{
	if (CurrentFloor)
	{
		FText Text = FText::Format(
			FText::FromString("B {0}F"),
			FText::AsNumber(FMath::Abs(Floor))
		);
		CurrentFloor->SetText(Text);
	}
}
