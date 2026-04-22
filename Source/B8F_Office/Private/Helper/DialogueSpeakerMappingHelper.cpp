// Fill out your copyright notice in the Description page of Project Settings.


#include "Helper/DialogueSpeakerMappingHelper.h"

ADialogueSpeakerMappingHelper::ADialogueSpeakerMappingHelper()
{

}

void ADialogueSpeakerMappingHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADialogueSpeakerMappingHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AActor* ADialogueSpeakerMappingHelper::GetActorFromName(FName Name)
{
	TObjectPtr<AActor>* Found = ActorMapping.Find(Name);
	if (Found)
	{
		return *Found;
	}
	else
	{
		return nullptr;
	}
}

