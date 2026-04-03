// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogics/StageStartArea.h"
#include "GameLogics/TeleportArea.h"
#include "Components/BoxComponent.h"

AStageStartArea::AStageStartArea()
{

}

void AStageStartArea::BeginPlay()
{
	Super::BeginPlay();
}

void AStageStartArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}