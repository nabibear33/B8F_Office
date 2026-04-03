

#include "Widgets/InfoPanelWidget.h"
#include "GameManager/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "GameInstances/SaveGameInstanceSubsystem.h"
#include "Save/MainSaveGame.h"
#include "Widgets/AnomalyStatusEntry.h"

void UInfoPanelWidget::PopulateFromMap(const TMap<EAnomalyType, EAnomalyStatus>& AnomalyRecord)
{
	// UE_LOG(LogTemp, Warning, TEXT("PopulateFromMap called, Record count: %d"), AnomalyRecord.Num());

	EntryContainer->ClearChildren();

	for (const auto& [Type, Status] : AnomalyRecord)
	{
		/*
		UE_LOG(LogTemp, Warning, TEXT("Type: %s, Status: %s"),
			*UEnum::GetValueAsString(Type),
			*UEnum::GetValueAsString(Status));
		*/

		UAnomalyStatusEntry* Entry = CreateWidget<UAnomalyStatusEntry>(this, EntryWidget);
		if (!Entry)
		{
			UE_LOG(LogTemp, Error, TEXT("CreateWidget failed for Type: %s"), *UEnum::GetValueAsString(Type));
			continue;
		}

		Entry->UpdateEntry(Type, Status);
		EntryContainer->AddChild(Entry);
	}

	// UE_LOG(LogTemp, Warning, TEXT("PopulateFromMap done, Container children: %d"), EntryContainer->GetChildrenCount());
}

void UInfoPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AGameManager* GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	if (GameManager)
	{
		GameManager->OnInfoPanelUpdated.AddDynamic(this, &UInfoPanelWidget::OnInfoPanelUpdated);
	}

	DrawCurrentFloor(GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>()->GetSaveGame()->GetCurrentFloor());
	DrawAnomalyRecord();
}

void UInfoPanelWidget::DrawAnomalyRecord()
{
	USaveGameInstanceSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameInstanceSubsystem>();
	if (SaveSubsystem && SaveSubsystem->GetSaveGame())
	{
		PopulateFromMap(SaveSubsystem->GetSaveGame()->GetAnomalyRecord());
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
