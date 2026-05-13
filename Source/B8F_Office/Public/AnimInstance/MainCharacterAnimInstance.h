// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameLogics/Types.h"
#include "MainCharacterAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class B8F_OFFICE_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

private:

};
