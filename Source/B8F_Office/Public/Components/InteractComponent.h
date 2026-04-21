// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameLogics/Delegates.h"
#include "InteractComponent.generated.h"

class USphereComponent;
class UInteractWidget;
class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B8F_OFFICE_API UInteractComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	FOnInteractableEntered OnInteractableEntered;

	UPROPERTY()
	FOnInteractableLeft OnInteractableLeft;

	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInteractWidget> InteractWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InteractWidgetComponent;

	void SetInteractEnabled();

	void SetInteractDisabled();


protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> InteractableArea;

	UPROPERTY()
	TObjectPtr<UInteractWidget> InteractWidget;

	UPROPERTY(VisibleAnywhere)
	bool bIsOwnerInteractable = false;

public:
	FORCEINLINE bool IsOwnerInteractable() { return bIsOwnerInteractable; }
		
};
