// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/AnomalyRow.h"
#include "CollectedAnomalyList.generated.h"

class UWrapBox;
class UCollectedAnomalyDetail;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UCollectedAnomalyList : public UUserWidget
{
	GENERATED_BODY()

public:
	void AnomalyDetailWidgetUpdated(FText AnomalyName, UTexture2D* Texture, FText AnomalyDetail);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> AnomalyDataTable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> AnomalyItemClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> AnomalyItemWrapper;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> NotSeenTexture;
	

};
