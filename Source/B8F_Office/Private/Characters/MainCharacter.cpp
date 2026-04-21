

#include "Characters/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
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
	// UE_LOG(LogTemp, Warning, TEXT("Try Interact Function Executed"));

	if (InteractableCount == 0) return;

	CurrentInteractTarget->Interact_Implementation();
}

void AMainCharacter::SprintStart()
{
	if (Controller)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AMainCharacter::SprintStop()
{
	if (Controller)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AMainCharacter::OnInteractableEntered(AActor* InteractableActor, AMainCharacter* MainCharacter)
{
	TScriptInterface<IInteractable> Interactable = InteractableActor;
	if (Interactable)
	{
		CurrentInteractTarget = Interactable;
		InteractableCount++;
	}
}

void AMainCharacter::OnInteractableLeft(AActor* InteractableActor, AMainCharacter* MainCharacter)
{
	CurrentInteractTarget = nullptr;
	InteractableCount--;
}

void AMainCharacter::ResetInteractableCount()
{
	CurrentInteractTarget = nullptr;
	InteractableCount = 0;
}
