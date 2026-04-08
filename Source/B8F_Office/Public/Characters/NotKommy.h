// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/InteractableCharacter.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "NotKommy.generated.h"

class AAIController;

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ANotKommy : public AInteractableCharacter
{
	GENERATED_BODY()

public:
	ANotKommy();
	void ChasePlayer(AActor* Player);
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	FOnPlayDeathScene OnPlayDeathScene;

	UFUNCTION()
	void OnNotKommyTriggerAreaTriggered(AActor* TriggeringArea, AActor* OtherActor);
protected:
	virtual void BeginPlay() override;

	virtual void SetNormal() override;


private:

	TObjectPtr<AAIController> Controller;

	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState;

	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	
	UPROPERTY()
	FVector InitialLocation;
};
