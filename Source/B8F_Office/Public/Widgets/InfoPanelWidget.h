
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLogics/Types.h"
#include "InfoPanelWidget.generated.h"

class UTextBlock;
class UAnomalyStatusEntry;
class UWrapBox;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UInfoPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnomalyStatusEntry> EntryWidget;

	void PopulateFromRecord(const TArray<FAnomalyEntry>& AnomalyRecord);

private:
	virtual void NativeConstruct() override;

	void DrawAnomalyRecord();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentFloor;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* EntryContainer;

	UFUNCTION()
	void OnInfoPanelUpdated(int32 Floor, EAnomalyType AnomalyType, EAnomalyStatus AnomalyStatus);
	void DrawCurrentFloor(int32 Floor);
};
