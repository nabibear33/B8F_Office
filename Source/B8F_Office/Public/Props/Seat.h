// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/BaseProp.h"
#include "Seat.generated.h"



/**
 * 
 */
UCLASS()
class B8F_OFFICE_API ASeat : public ABaseProp
{
	GENERATED_BODY()
	
public:
	ASeat();

	void DisableCollision();

protected:

	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SeatMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SitPoint;

public:
	FORCEINLINE FTransform GetSitPointTransform() { return SitPoint->GetComponentTransform(); }
};
