// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

class UDialogueComponent;
class UDataTable;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainCharacterController();

	virtual void SetControlRotation(const FRotator& NewRotation) override;

	void StartDialogue(UDataTable* DialogueRows, FName ID);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDialogueComponent> DialogueComponent;
};
