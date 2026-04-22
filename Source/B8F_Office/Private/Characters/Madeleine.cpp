// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Madeleine.h"
#include "GameLogics/TriggerArea.h"
#include "Controllers/MainCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/DialogueComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/InteractComponent.h"


AMadeleine::AMadeleine()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
}

void AMadeleine::BeginPlay()
{
	Super::BeginPlay();
}

void AMadeleine::Interact_Implementation()
{
	if (!bPlayerWinRedLight) return;

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		if (!DialogueDataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("No DataTable linked."));
			return;
		}

		PC->StartDialogue(this, DialogueDataTable, FName(TEXT("Madeleine_WinGameAfter")));
	}
}

void AMadeleine::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType == EAnomalyType::EAT_RedLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegate Binding Redlight"));
		LinkedArea->OnAreaTriggered.RemoveDynamic(this, &AMadeleine::StartGame);
		LinkedArea->OnAreaTriggered.AddDynamic(this, &AMadeleine::StartGame);
		if (FinishArea)
		{
			FinishArea->OnAreaTriggered.RemoveDynamic(this, &AMadeleine::PlayerWinRedLight);
			FinishArea->OnAreaTriggered.AddDynamic(this, &AMadeleine::PlayerWinRedLight);
		}
		AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->GetDialogueComponent()->OnDialogueEnded.AddDynamic(this, &AMadeleine::OnDialogueEnded);
		}
		EnableCharacterMesh();
		InteractComponent->SetInteractEnabled();
	}
	else
	{
		DisableCharacterMesh();
		InteractComponent->SetInteractDisabled();
	}
}

void AMadeleine::StartGame(AActor* TriggeringArea, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Madeleine StartGame Triggered"));
	
	SetViewTargetChanged();

	// Start Dialogue
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			StartDialogue(FName(TEXT("Madeleine_001")));
		},
		2.0f,
		false
	);

}

void AMadeleine::SetViewTargetChanged()
{
	bIsViewTargetChanged = true;
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->SetViewTargetWithBlend(
			this,
			1.5f,
			EViewTargetBlendFunction::VTBlend_Cubic,
			0.0f,
			false
		);
	}
}

void AMadeleine::OnDialogueEnded()
{
	if (!bIsViewTargetChanged) return;

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMainCharacter* Player = Cast<AMainCharacter>(PC->GetPawn());
		if (Player)
		{
			PC->SetViewTargetWithBlend(
				Player,
				1.5f,
				EViewTargetBlendFunction::VTBlend_Cubic,
				0.0f,
				false
			);
		}
	}
	bIsViewTargetChanged = false;
}

void AMadeleine::StartDialogue(FName ID)
{
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		if (!DialogueDataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("No DataTable linked."));
			return;
		}

		PC->StartDialogue(this, DialogueDataTable, ID);
	}
}

void AMadeleine::PlayerWinRedLight(AActor* TriggeringArea, AActor* OtherActor)
{
	bPlayerWinRedLight = true;

	// set madeleine to rotate towards player here

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->SetViewTargetWithBlend(
			this,
			0.5f,
			EViewTargetBlendFunction::VTBlend_Cubic,
			0.0f,
			false
		);
	}

	StartDialogue(FName(TEXT("Madeleine_WinGame")));
}
