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
	ClearSongPyeons();

	if(AnomalyType == EAnomalyType::EAT_SongPyeon)
	{
			LinkedArea->OnAreaTriggered.RemoveDynamic(this, &ASongPyeonSpawner::SpawnSongPyeon);
			LinkedArea->OnAreaTriggered.AddDynamic(this, &ASongPyeonSpawner::SpawnSongPyeon);
	}
	else
	{
		SetNormal();
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
		FMath::RandRange(-2.f * SpawnDivergence, 2.f * SpawnDivergence),
		FMath::RandRange(-2.f * SpawnDivergence, 2.f * SpawnDivergence),
		0.f
	);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AStaticMeshActor* SongPyeon = GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(), SpawnLocation, FRotator::ZeroRotator
	);
	SpawnedSongpyeons.Add(SongPyeon);

	if (SongPyeon && SongPyeonMesh)
	{
		UStaticMeshComponent* MeshComp = SongPyeon->GetStaticMeshComponent();
		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetStaticMesh(SongPyeonMesh);
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
		MeshComp->AddImpulse(FVector(
			FMath::RandRange(-SpawnDivergence, SpawnDivergence),
			FMath::RandRange(-SpawnDivergence, SpawnDivergence),
			FMath::RandRange(-SpawnVelocity, -0.7f * SpawnVelocity)
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

void ASongPyeonSpawner::ClearSongPyeons()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	for(AActor* SongPyeon : SpawnedSongpyeons)
	{
		if (SongPyeon)
		{
			SongPyeon->Destroy();
		}
	}
	SpawnedSongpyeons.Empty();
	CurrentSpawnCount = 0;
}


