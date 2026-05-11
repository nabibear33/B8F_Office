// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/AnomalyProp.h"
#include "SongPyeonSpawner.generated.h"

/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ASongPyeonSpawner : public AAnomalyProp
{
	GENERATED_BODY()
	
public:
	ASongPyeonSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void OnStageStart(EAnomalyType AnomalyType) override;
	virtual void SetNormal() override;

private:
	void SpawnSingleSongPyeon();

	UFUNCTION()
	void SpawnSongPyeon(AActor* TriggeringActor, AActor* TriggeredCharacter);

	void ClearSongPyeons();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> SongPyeonMesh;

	UPROPERTY(EditAnywhere)
	int32 SpawnRate = 50;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnCount = 100;

	UPROPERTY(EditAnywhere)
	float SpawnDivergence = 50.f;

	UPROPERTY(EditAnywhere)
	float SpawnVelocity = 200.f;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentSpawnCount = 0;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedSongpyeons;
};
