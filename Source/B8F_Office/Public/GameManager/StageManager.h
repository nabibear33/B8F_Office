
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameLogics/Types.h"
#include "GameLogics/Delegates.h"
#include "StageManager.generated.h"



class ANotKommy;
class ATriggerArea;
class IInteractable;

USTRUCT(BlueprintType)
struct FInteractableList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<AActor>> Interactables;
};

UCLASS()
class B8F_OFFICE_API AStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AStageManager();

	void ResetStage();
	void SetNormalStage();

	UPROPERTY()
	FOnStageStart OnStageStart;
protected:
	virtual void BeginPlay() override;

	// Debugging
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EStageState StageState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnomalyType AnomalyType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAnomalyStatus AnomalyStatus;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AMainCharacter> Player;

	UPROPERTY(EditAnywhere)
	float AnomalyProbability = 0.5f;

	UPROPERTY(EditAnywhere)
	bool bTestAnomaly;

	UPROPERTY(EditAnywhere)
	EAnomalyType TestAnomalyType;

	UPROPERTY(VisibleAnywhere)
	FInteractableList CurrentStageInteractableList;

	UPROPERTY(EditAnywhere)
	TMap<EAnomalyType, FInteractableList> AnomalyInteractableMap;

public:
	FORCEINLINE EStageState GetStageState() { return StageState; }
	FORCEINLINE EAnomalyType GetAnomalyType() { return AnomalyType; }
	FORCEINLINE EAnomalyStatus GetAnomalyStatus() { return AnomalyStatus; }
	FORCEINLINE int32 GetAnomalyTotalCount() { return static_cast<int32>(EAnomalyType::EAT_MAX) - 1; }
};
