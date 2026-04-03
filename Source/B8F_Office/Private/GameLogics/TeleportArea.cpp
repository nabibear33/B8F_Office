

#include "GameLogics/TeleportArea.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/MainCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"

ATeleportArea::ATeleportArea()
{
}

void ATeleportArea::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleportArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	TeleportToCounterpart(OtherActor);
}

void ATeleportArea::TeleportToCounterpart(AActor* Actor)
{
	AMainCharacter* OverlappedCharacter = Cast<AMainCharacter>(Actor);
	if (!OverlappedCharacter) return;
	APlayerController* PlayerController = Cast<APlayerController>(OverlappedCharacter->GetController());
	if (!PlayerController) return;

	UE_LOG(LogTemp, Warning, TEXT("Teleport!"));

	FTransform SourceTransform = GetActorTransform();
	FTransform TargetTransform = GetCounterpart()->GetActorTransform();

	FQuat ControllerQuaternion = PlayerController->GetControlRotation().Quaternion();
	FQuat CharacterLocalRotationToArea = SourceTransform.GetRotation().Inverse() * ControllerQuaternion;
	FQuat CharacterWorldRotation = TargetTransform.GetRotation() * CharacterLocalRotationToArea;
	PlayerController->SetControlRotation(CharacterWorldRotation.Rotator());

	FVector CharacterLocalPositionToArea = SourceTransform.InverseTransformPosition(OverlappedCharacter->GetActorLocation());
	FVector CharacterWorldPosition = TargetTransform.TransformPosition(CharacterLocalPositionToArea);
	OverlappedCharacter->SetActorLocation(CharacterWorldPosition, false, nullptr, ETeleportType::TeleportPhysics);

	UCharacterMovementComponent* MovementComponent = OverlappedCharacter->GetCharacterMovement();
	FQuat RotationDelta = TargetTransform.GetRotation() * SourceTransform.GetRotation();
	MovementComponent->Velocity = RotationDelta.RotateVector(MovementComponent->Velocity);
}