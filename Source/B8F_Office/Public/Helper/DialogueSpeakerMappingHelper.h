// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueSpeakerMappingHelper.generated.h"

UCLASS()
class B8F_OFFICE_API ADialogueSpeakerMappingHelper : public AActor
{
	GENERATED_BODY()
	
public:
	ADialogueSpeakerMappingHelper();
	virtual void Tick(float DeltaTime) override;

	AActor* GetActorFromName(FName Name);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<AActor>> ActorMapping;

};
