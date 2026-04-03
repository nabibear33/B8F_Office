// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Characters/BaseCharacter.h"
#include "MainCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class UInputComponent;
class UCameraComponent;

UCLASS()
class B8F_OFFICE_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDeath();
	void OnRevive();

protected:
	virtual void BeginPlay() override;

	// Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FirstPersonCamera;

private:
	// Input Actions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void SprintStart();
	void SprintStop();
	
	// Attributes
	UPROPERTY(EditAnywhere, Category = Attributes)
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Attributes)
	float SprintSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = Camera)
	FVector CameraPosition = FVector(0.f, 0.f, 64.f);

	UPROPERTY()
	FVector InitialLocation;

	UPROPERTY()
	FRotator InitialRotation;
};
