
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/BaseArea.h"
#include "StageStartArea.generated.h"


UCLASS()
class B8F_OFFICE_API AStageStartArea : public ABaseArea
{
	GENERATED_BODY()

public:
	AStageStartArea();

protected:
	virtual void BeginPlay() override;

private:

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
