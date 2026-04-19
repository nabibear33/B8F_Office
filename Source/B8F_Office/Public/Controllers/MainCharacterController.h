// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MainCharacterController.generated.h"

class UDialogueComponent;
class UDataTable;
class UInputMappingContext;
class UInputAction;

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

	void SetDialogueIMC();

	void EndDialogue();

	void SetDefaultIMC();
	
	void OnDialogueWidgetReady();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_AdvanceDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_NavigateChoice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_SelectChoice;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDialogueComponent> DialogueComponent;

	void OnAdvanceDialogue();

	void OnNavigateChoice(const FInputActionValue& Value);

	void OnSelectChoice();
};
