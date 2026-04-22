#pragma once

#include "GameLogics/Types.h"

#include "CoreMinimal.h"
#include "Delegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathAndReset);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSceneChoiceSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeftTimeUpdated, float, LeftTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, FName, DialogueID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHighlightedChoiceUpdated, int32, CurrentHighlightedChoice);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableLeft, AActor*, InteractableActor, AMainCharacter*, MainCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableEntered, AActor*, InteractableActor, AMainCharacter*, MainCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueUpdated, const FDialogueRow&, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayDeathScene, EDeathSceneType, DeathSceneType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageStart, EAnomalyType, AnomalyType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAreaTriggered, AActor*, TriggeringActor, AActor*, TriggeredCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInfoPanelChanged, int32, Floor, EAnomalyType, AnomalyType, EAnomalyStatus, AnomalyStatus);

UCLASS()
class UDelegates : public UObject
{
    GENERATED_BODY()
};