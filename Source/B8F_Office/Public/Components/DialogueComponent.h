// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameLogics/Delegates.h"
#include "DataTables/DialogueRow.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B8F_OFFICE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartDialogue(UDataTable* DialogueRows, FName ID);
	void AdvanceDialogue(FName ChoiceRowID = NAME_None);
	void EndDialogue();

	void NavigateCurrentChoiceIdx(float Value);
	void OnSelectCurrentChoice();

	UPROPERTY()
	FOnDialogueUpdated OnDialogueUpdated;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> DialogueDataTable;

	UPROPERTY(VisibleAnywhere)
	FName CurrentRowID;

	TOptional<FDialogueRow> CurrentRow;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentChoiceIdx = -1;

	UPROPERTY(VisibleAnywhere)
	bool bIsWaitingForChoice = false;

	bool IsRowRequiresChoice(FDialogueRow* Row);
	bool IsLastRow(FDialogueRow* Row);
public:
	FORCEINLINE void SetDialogueDataTable(UDataTable* DataTable) { DialogueDataTable = DataTable; }
	FORCEINLINE void SetCurrentRowID(FName ID) { CurrentRowID = ID; }
	FORCEINLINE bool IsCurrentRowHasChoices() const { return CurrentRow.IsSet() && !CurrentRow->Choices.IsEmpty(); }
	FORCEINLINE int32 GetCurrentChoiceNum() const { return CurrentRow.IsSet() ? CurrentRow->Choices.Num() : 0; }
};
