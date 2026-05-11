// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/Progressible.h"
#include "BaseProp.generated.h"

class ATriggerArea;
class UInteractComponent;

UCLASS()
class B8F_OFFICE_API ABaseProp : public AActor, public IInteractable, public IProgressible
{
	GENERATED_BODY()
	
public:	
	ABaseProp();

	virtual UInteractComponent* GetInteractComponent() override;

	FOnGameProgressUpdated OnGameProgressUpdated;

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerArea> LinkedArea;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInteractComponent> InteractComponent;
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsInInteractRange = false;

	UPROPERTY(EditAnywhere)
	FName LinkedProgressName;

	virtual void AdvanceProgress(FName Name) override;
};
