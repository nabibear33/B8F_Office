// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Madeleine.h"
#include "GameLogics/TriggerArea.h"
#include "Controllers/MainCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/DialogueComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/InteractComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"


AMadeleine::AMadeleine()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
}

void AMadeleine::BeginPlay()
{
	Super::BeginPlay();

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		CachedPlayer = Cast<AMainCharacter>(PC->GetPawn());
	}
}

void AMadeleine::Interact_Implementation()
{
	if (StageStatus != ERedLightStageStatus::ERSS_Pass) return;

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

void AMadeleine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckLeftTime(DeltaTime);
	CheckMovement();
}

void AMadeleine::CheckMovement()
{
	if (!bIsRedLight || !CachedPlayer) return;

	float Speed = CachedPlayer->GetCharacterMovement()->Velocity.Size();
	if (Speed > 10.f)
	{
		OnPhaseTransition(ERedLightStageStatus::ERSS_RedLightMoved);
	}
}

void AMadeleine::CheckLeftTime(float DeltaTime)
{
	TimeLeft -= DeltaTime;

	if (TimeLeft <= 0.f)
	{
		OnPhaseTransition(ERedLightStageStatus::ERSS_TimeOut);
	}
}

void AMadeleine::OnStageStart(EAnomalyType AnomalyType)
{
	if(AnomalyType == EAnomalyType::EAT_RedLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegate Binding Redlight"));
		LinkedArea->OnAreaTriggered.RemoveDynamic(this, &AMadeleine::OnAreaTriggered);
		LinkedArea->OnAreaTriggered.AddDynamic(this, &AMadeleine::OnAreaTriggered);
		if (FinishArea)
		{
			FinishArea->OnAreaTriggered.RemoveDynamic(this, &AMadeleine::OnFinishAreaTriggerd);
			FinishArea->OnAreaTriggered.AddDynamic(this, &AMadeleine::OnFinishAreaTriggerd);
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

void AMadeleine::OnAreaTriggered(AActor* TriggeringArea, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Madeleine OnAreaTriggered."));
	OnPhaseTransition(ERedLightStageStatus::ERSS_Entered);
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

void AMadeleine::OnDialogueEnded(FName DialogueID)
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
	
	if (DialogueID == FName(TEXT("Madeleine_StartGame")))
	{
		OnPhaseTransition(ERedLightStageStatus::ERSS_OnPlaying);
	}
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

void AMadeleine::OnFinishAreaTriggerd(AActor* TriggeringArea, AActor* OtherActor)
{
	SetActorTickEnabled(false);
	OnPhaseTransition(ERedLightStageStatus::ERSS_Pass);

}

void AMadeleine::OnPassedGame()
{
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

void AMadeleine::OnPhaseTransition(ERedLightStageStatus Status)
{
	SetPhase(Status);

	switch (StageStatus)
	{
		case ERedLightStageStatus::ERSS_Entered:
			OnStageEntered();
			break;

		case ERedLightStageStatus::ERSS_OnPlaying:
			MainGame();
			break;


		case ERedLightStageStatus::ERSS_TimeOut:
			LoseGame(FName(TEXT("Madeleine_TimeOut")));
			break;
		case ERedLightStageStatus::ERSS_RedLightMoved:
			LoseGame(FName(TEXT("Madeleine_RedLightMoved")));
			break;
		case ERedLightStageStatus::ERSS_Pass:
			OnPassedGame();
			break;
	}
}

void AMadeleine::OnStageEntered()
{
	SetViewTargetChanged();

	// Start Dialogue after camera walk
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

void AMadeleine::MainGame()
{
	// Tick function checks the lose condition
	SetActorTickEnabled(true);
	
	// Reverse the light per 1 sec (temp)
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			bIsRedLight = !bIsRedLight;
		},
		1.0f,
		true
	);
}

void AMadeleine::LoseGame(FName RowName)
{
	SetActorTickEnabled(false);

	// get player location
	FVector DistanceVector = (CachedPlayer->GetActorLocation() - GetActorLocation());
	float Distance = DistanceVector.Size2D() - 100.f;
	FVector Direction = FVector(DistanceVector.X, DistanceVector.Y, 0.f).GetSafeNormal();
	
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->MaxAcceleration = 100000.f;
	MovementComponent->MaxWalkSpeed = 6400.f;

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->MoveToLocation(GetActorLocation() + Direction * Distance);
	}

	StartDialogue(RowName);

	// kill player here
}
