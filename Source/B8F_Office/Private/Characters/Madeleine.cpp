// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Madeleine.h"
#include "GameLogics/TriggerArea.h"
#include "Controllers/MainCharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/DialogueComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/InteractComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstances/EventBusSubsystem.h"
#include "AIController.h"
#include "HUD/MainHUD.h"
#include "Kismet/GameplayStatics.h"


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

	InitialLocation = GetActorLocation();

	PostProcessVolume = Cast<APostProcessVolume>(
		UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()));
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
	BroadcastToWidget();
}

void AMadeleine::BroadcastToWidget()
{
	UEventBusSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEventBusSubsystem>();
	if (Subsystem)
	{
		Subsystem->OnLeftTimeUpdated.Broadcast(TimeLeft);
	}
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
	SetActorLocation(InitialLocation);
	if(AnomalyType == EAnomalyType::EAT_RedLight)
	{
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
	if (bIsViewTargetChanged)
	{
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

	
	if (DialogueID == FName(TEXT("Madeleine_StartGame")))
	{
		OnPhaseTransition(ERedLightStageStatus::ERSS_OnPlaying);
	}

	if (DialogueID == FName(TEXT("Madeleine_TimeOut")) || DialogueID == FName(TEXT("Madeleine_RedLightMoved")))
	{
		OnPhaseTransition(ERedLightStageStatus::ERSS_PlayDeathScene);
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
	GetWorldTimerManager().ClearTimer(LightFlipTimerHandle);
	// set madeleine to rotate towards player here

	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
		if (HUD)
		{
			HUD->HideLeftTimeWidget();
		}
		
		bIsViewTargetChanged = true;
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
	UEventBusSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEventBusSubsystem>();

	switch (StageStatus)
	{
		case ERedLightStageStatus::ERSS_Entered:
			OnStageEntered();
			break;

		case ERedLightStageStatus::ERSS_OnPlaying:
			MainGame();
			break;


		case ERedLightStageStatus::ERSS_TimeOut:
			ChangeLightsColor(FLinearColor::Red, Subsystem);
			LoseGame(FName(TEXT("Madeleine_TimeOut")));
			break;
		case ERedLightStageStatus::ERSS_RedLightMoved:
			ChangeLightsColor(FLinearColor::Red, Subsystem);
			LoseGame(FName(TEXT("Madeleine_RedLightMoved")));
			break;
		case ERedLightStageStatus::ERSS_PlayDeathScene:
			PlayDeathScene();
			break;
		case ERedLightStageStatus::ERSS_Pass:
			ChangeLightsColor(FLinearColor::White, Subsystem);
			OnPassedGame();
			break;
	}
}

void AMadeleine::ChangeLightsColor(const FLinearColor& Color, UEventBusSubsystem* Subsystem)
{
	PostProcessVolume->Settings.SceneColorTint = Color;
	Subsystem->OnLightColorUpdated.Broadcast(Color);
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

	// show left time widget
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
		if (HUD)
		{
			HUD->ShowLeftTimeWidget();
		}
	}
	
	// Reverse the light per 1 sec (temp)
	GetWorld()->GetTimerManager().SetTimer(
		LightFlipTimerHandle,
		[this]()
		{
			bIsRedLight = !bIsRedLight;
			UEventBusSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEventBusSubsystem>();
			if (Subsystem)
			{
				FLinearColor Color = (bIsRedLight) ? FLinearColor::Red : FLinearColor::Green;
				UE_LOG(LogTemp, Warning, TEXT("Change Color BroadCast"));
				ChangeLightsColor(Color, Subsystem);
			}
		},
		FlipInterval,
		true
	);
}

void AMadeleine::LoseGame(FName RowName)
{
	GetWorldTimerManager().ClearTimer(LightFlipTimerHandle);
	AMainCharacterController* PC = Cast<AMainCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
		if (HUD)
		{
			HUD->HideLeftTimeWidget();
		}
	}

	SetActorTickEnabled(false);

	MoveToPlayer();

	StartDialogue(RowName);
}

void AMadeleine::MoveToPlayer()
{
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
}

void AMadeleine::PlayDeathScene()
{
	OnPlayCutscene.Broadcast(ECutsceneName::ECN_RedLight);
}
