#pragma once

#include "GameLogics/Types.h"

#include "CoreMinimal.h"
#include "Delegates.generated.h"

// Cut Scene
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerRevive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayCutscene, ECutsceneName, CutsceneName);

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

// Main Menu
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMainMenuStatusUpdated, EMainMenuStatus, MainMenuStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCollectionItemClicked, FText, AnomalyName, UTexture2D*, Texture, FText, AnomalyDetail);

// Global Game State
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameProgressUpdated, FName, ProgressName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseUpdated, EGamePhase, GamePhase);


UCLASS()
class UDelegates : public UObject
{
    GENERATED_BODY()
};