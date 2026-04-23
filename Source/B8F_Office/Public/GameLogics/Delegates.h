#pragma once

#include "GameLogics/Types.h"

#include "CoreMinimal.h"
#include "Delegates.generated.h"

// Death Scene
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathAndReset);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayDeathScene, EDeathSceneType, DeathSceneType);

// Dialogue Component Logic
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSceneChoiceSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, FName, DialogueID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHighlightedChoiceUpdated, int32, CurrentHighlightedChoice);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueUpdated, const FDialogueRow&, Row);

// Red Light Anomaly
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLightColorUpdated, FLinearColor, Color);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeftTimeUpdated, float, LeftTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseUpdated, ERedLightStageStatus, StageStatus);

// Interact Component Logic
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableLeft, AActor*, InteractableActor, AMainCharacter*, MainCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableEntered, AActor*, InteractableActor, AMainCharacter*, MainCharacter);

// Stage Start Logic
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageStart, EAnomalyType, AnomalyType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAreaTriggered, AActor*, TriggeringActor, AActor*, TriggeredCharacter);

// Info Panel Update
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInfoPanelChanged, int32, Floor, EAnomalyType, AnomalyType, EAnomalyStatus, AnomalyStatus);

UCLASS()
class UDelegates : public UObject
{
    GENERATED_BODY()
};