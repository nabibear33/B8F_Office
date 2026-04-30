// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ProgressComponent.h"

UProgressComponent::UProgressComponent()
{
}


void UProgressComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UProgressComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

