// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameLogics/Delegates.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B8F_OFFICE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartDialogue(APlayerController* Instigator);
	void AdvanceDialogue(FName ChoiceRowID = NAME_None);
	void EndDialogue();

	UPROPERTY()
	FOnDialogueUpdated OnDialogueUpdated;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> DialogueTable;

	UPROPERTY(EditAnywhere)
	FName StartRowID;

	FName CurrentRowID;

};
