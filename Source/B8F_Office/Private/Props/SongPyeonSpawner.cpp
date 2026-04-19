// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/SongPyeonSpawner.h"
#include "Engine/StaticMeshActor.h"
#include "GameLogics/TriggerArea.h"

ASongPyeonSpawner::ASongPyeonSpawner()
{
}

void ASongPyeonSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ASongPyeonSpawner::OnStageStart(EAnomalyType AnomalyType)
{
	switch (AnomalyType)
	{
		case EAnomalyType::EAT_SongPyeon:
			LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ASongPyeonSpawner::SpawnSongPyeon);
			LinkedArea->OnAreaTriggered.AddDynamic(this, &ASongPyeonSpawner::SpawnSongPyeon);
			break;
		default:
			SetNormal();
			break;
	}
}

void ASongPyeonSpawner::SetNormal()
{
}

void ASongPyeonSpawner::SpawnSingleSongPyeon()
{
	if (CurrentSpawnCount > MaxSpawnCount)
	{
		return;
	}

	FVector SpawnLocation = GetActorLocation() + FVector(
		FMath::RandRange(-100.f, 100.f),
		FMath::RandRange(-100.f, 100.f),
		0.f
	);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AStaticMeshActor* SongPyeon = GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(), SpawnLocation, FRotator::ZeroRotator
	);

	if (SongPyeon && SongPyeonMesh)
	{
		UStaticMeshComponent* MeshComp = SongPyeon->GetStaticMeshComponent();
		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetStaticMesh(SongPyeonMesh);
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->AddImpulse(FVector(
			FMath::RandRange(-50.f, 50.f),
			FMath::RandRange(-50.f, 50.f),
			FMath::RandRange(50.f, 150.f)
		));
	}

	CurrentSpawnCount++;
}

void ASongPyeonSpawner::SpawnSongPyeon(AActor* TriggeringActor, AActor* TriggeredCharacter)
{
	CurrentSpawnCount = 0;

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASongPyeonSpawner::SpawnSingleSongPyeon,
		1.f / SpawnRate,
		true
	);
}


