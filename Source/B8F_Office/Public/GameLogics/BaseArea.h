
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Delegates.h"
#include "BaseArea.generated.h"

class UBoxComponent;

UCLASS()
class B8F_OFFICE_API ABaseArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseArea();

	UPROPERTY()
	FOnAreaTriggered OnAreaTriggered;

	virtual void EnableArea();
	virtual void DisableArea();

	FOnGameProgressUpdated OnGameProgressUpdated;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnStageStart(EAnomalyType AnomalyType);

	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetNormal();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;

private:
	bool bIsEnabled = false;

	UPROPERTY(EditAnywhere)
	FName LinkedProgress;

public:
	FORCEINLINE bool IsAreaEnabled() { return bIsEnabled; }
	FORCEINLINE bool IsAreaDisabled() { return !bIsEnabled; }
};
