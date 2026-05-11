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

	if (InteractComponent)
	{
		//InteractComponent->OnInteractableEntered.AddDynamic(this, &AInteractableCharacter::OnInteractableEntered);
		//InteractComponent->OnInteractableLeft.AddDynamic(this, &AInteractableCharacter::OnInteractableLeft);
	}
}

void AInteractableCharacter::OnStageStart(EAnomalyType AnomalyType)
{
}

void AInteractableCharacter::OnInteractableEntered(AActor* InteractableActor, AMainCharacter* MainCharacter)
{
	bIsInInteractRange = true;
}

void AInteractableCharacter::OnInteractableLeft(AActor* InteractableActor, AMainCharacter* MainCharacter)
{
	bIsInInteractRange = false;
}

void AInteractableCharacter::SetNormal()
{
	InteractComponent->SetInteractDisabled();
	DisableCharacterMesh();
}

void AInteractableCharacter::DisableCharacterMesh()
{
	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractableCharacter::EnableCharacterMesh()
{
	GetMesh()->SetVisibility(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

