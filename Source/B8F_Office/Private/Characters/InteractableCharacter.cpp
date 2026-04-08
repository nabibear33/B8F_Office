// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacter.h"
#include "GameManager/StageManager.h"
#include "Components/InteractComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


AInteractableCharacter::AInteractableCharacter()
{
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

FText AInteractableCharacter::GetInteractHintText()
{
	return FText(FText::FromString(TEXT("Interact")));
}

void AInteractableCharacter::BeginPlay()
{
	Super::BeginPlay();

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &AInteractableCharacter::OnStageStart);
	}
}

void AInteractableCharacter::OnStageStart(EAnomalyType AnomalyType)
{
}

UInteractComponent* AInteractableCharacter::GetInteractComponent()
{
	return InteractComponent;
}

void AInteractableCharacter::OnInteractableEntered(AActor* InteractableActor, AMainCharacter* MainCharacter)
{
	bIsInteractable = true;
}

void AInteractableCharacter::OnInteractableLeft()
{
	bIsInteractable = false;
}

void AInteractableCharacter::SetNormal()
{
	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

