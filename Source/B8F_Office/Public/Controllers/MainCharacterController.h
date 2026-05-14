// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "MainCharacterController.generated.h"

class UDialogueComponent;
class UDataTable;
class UInputMappingContext;
class UInputAction;
class AInteractableCharacter;

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

	void StartDialogue(UDataTable* DialogueRows, FName ID, EDialogueMode Mode);

	void SetDialogueIMC();

	UFUNCTION()
	void EndDialogue(FName DialogueID);

	void SetDefaultIMC();
	
	void OnDialogueWidgetReady();

	UFUNCTION()
	void OnGamePhaseUpdated(EGamePhase Phase);

	UFUNCTION()
	void OnCharacterStateUpdated(ECharacterState State);

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnCollectionButtonClicked();

	UFUNCTION()
	void OnSettingButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UFUNCTION()
	void OnPauseButtonClicked();

	UFUNCTION()
	void OnClickedBack();
	
	FOnPauseStatusUpdated OnPauseStatusUpdated;

	FOnGameProgressUpdated OnGameProgressUpdated;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Dialogue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_Pause;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_AdvanceDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_NavigateChoice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_SelectChoice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Pause;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDialogueComponent> DialogueComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AInteractableCharacter> DialogueTarget;

	void OnAdvanceDialogue();

	void OnNavigateChoice(const FInputActionValue& Value);

	void OnSelectChoice();

	UPROPERTY(VisibleAnywhere)
	bool bOnDialogue = false;

	UPROPERTY(VisibleAnywhere)
	EDialogueMode DialogueMode;

	UPROPERTY(VisibleAnywhere)
	bool bIsGamePaused;

	UPROPERTY(VisibleAnywhere)
	EPauseStatus CurrentPauseStatus;

	EPauseStatus GetParentStatus(EPauseStatus Status);

	void Pause();

	void Resume();
public:
	FORCEINLINE UDialogueComponent* GetDialogueComponent() const { return DialogueComponent; }
};
