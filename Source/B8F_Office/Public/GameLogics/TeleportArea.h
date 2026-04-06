
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/BaseArea.h"
#include "TeleportArea.generated.h"


UCLASS()
class B8F_OFFICE_API ATeleportArea : public ABaseArea
{
	GENERATED_BODY()
	
public:	
	ATeleportArea();

	void TeleportToCounterpart(AActor* OtherActor);

protected:
	virtual void BeginPlay() override;

private:
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ATeleportArea> CounterpartArea;


public:
	FORCEINLINE ATeleportArea* GetCounterpart() { return CounterpartArea; }
};
