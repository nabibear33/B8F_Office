// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogics/ProgressibleArea.h"
#include "GameInstances/GameSubsystem.h"

void AProgressibleArea::BeginPlay()
{
	Super::BeginPlay();

	UGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (Subsystem)
	{
		OnGameProgressUpdated.AddDynamic(Subsystem, &UGameSubsystem::OnProgressUpdated);
	}
}


void AProgressibleArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (LinkedProgressName != NAME_None)
	{
		AdvanceProgress(LinkedProgressName);
	}
}


void AProgressibleArea::AdvanceProgress(FName Name)
{
	OnGameProgressUpdated.Broadcast(Name);
}
