

#include "Characters/MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Props/Seat.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCamera->SetupAttachment(GetMesh(), FName("HeadSocket"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(CameraPosition);
	FirstPersonCamera->bUsePawnControlRotation = true;

	GetMesh()->SetOwnerNoSee(true);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnMontageStarted.AddDynamic(this, &AMainCharacter::OnMontageStarted);
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnMontageEnded);
	}

	check(GEngine != nullptr);

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Triggered, this, &AMainCharacter::TryInteract);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AMainCharacter::SprintStart);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AMainCharacter::SprintStop);
	}

}

void AMainCharacter::OnDeath()
{
	DisableInput(GetController<APlayerController>());
	GetMesh()->SetVisibility(false);
}

void AMainCharacter::OnRevive()
{
	SetActorLocation(InitialLocation);
	SetActorRotation(InitialRotation);
	GetMesh()->SetVisibility(true);
	EnableInput(GetController<APlayerController>());
	ResetInteractableCount();
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller)
	{
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementValue.X);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.Y);
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}

void AMainCharacter::TryInteract()
{
	if (InteractableCount == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("[Player] Interact"));
	CurrentInteractTarget->Interact_Implementation();
}

void AMainCharacter::SprintStart()
{
	bIsSprinting = true;
	if (Controller)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AMainCharacter::SprintStop()
{
	bIsSprinting = false;
	if (Controller)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AMainCharacter::OnInteractableUpdated(AActor* InteractableActor, FVector ActorLocation, FText InteractText)
{
	TScriptInterface<IInteractable> Interactable = InteractableActor;
	if (Interactable)
	{
		CurrentInteractTarget = Interactable;
		InteractableCount++;
	}
}

void AMainCharacter::OnInteractableLeft(AActor* InteractableActor)
{
	CurrentInteractTarget = nullptr;
	InteractableCount--;
}

void AMainCharacter::ResetInteractableCount()
{
	CurrentInteractTarget = nullptr;
	InteractableCount = 0;
}

void AMainCharacter::Sit(ASeat* Seat)
{
	Seat->DisableCollision();

	FTransform Transform = Seat->GetSitPointTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	SetActorLocation(Location);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->SetControlRotation(Rotation);
	}

	UE_LOG(LogTemp, Warning, TEXT("[Player] Play Sit Montage"));
	PlayAnimMontage(SitMontage, 1.0f, FName("StandToSit"));
	// ABP Blend Pose Timing issue -> lazy update
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			CharacterState = ECharacterState::ECS_Sit;	
		}, 
		0.5f, 
		false
	);
}

void AMainCharacter::Stand()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player] Play Stand Montage"));
	PlayAnimMontage(SitMontage, 1.0f, FName("SitToStand"));
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			CharacterState = ECharacterState::ECS_Idle;
		},
		0.5f,
		false
	);
}


void AMainCharacter::OnMontageStarted(UAnimMontage* AnimMontage)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Player] Disable input while playing anim montage"));
		// PC->DisableInput(PC);
		PC->SetIgnoreLookInput(true);
		PC->SetIgnoreMoveInput(true);
	}
}

void AMainCharacter::OnMontageEnded(UAnimMontage* AnimMontage, bool bInterrupted)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Player] Enable input after finishing anim montage"));
		// Actually not fit for the original purpose, but it work well...
		OnCharacterStateUpdated.Broadcast(CharacterState);
		// PC->EnableInput(PC);
		// PC->ResetIgnoreLookInput();
		// PC->ResetIgnoreMoveInput();
	}
}