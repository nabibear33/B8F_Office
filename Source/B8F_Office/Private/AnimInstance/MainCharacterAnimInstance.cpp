// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/MainCharacterAnimInstance.h"
#include "Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	UAnimInstance::NativeUpdateAnimation(DeltaSeconds);

	AMainCharacter* Player = Cast<AMainCharacter>(TryGetPawnOwner());
	if (!Player) return;
		
	bIsSprinting = Player->GetIsSprinting();
	CharacterState = Player->GetCharacterState();

	UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement();
	Speed = MoveComp->Velocity.Size2D();
}
