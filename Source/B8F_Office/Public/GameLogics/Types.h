#pragma once

#include "Types.generated.h"

UENUM(BlueprintType)
enum class EMainStageState : uint8
{
	EGS_OnStage UMETA(Displayname = "On Stage"),
	EGS_Intermediate UMETA(Displayname = "Intermediate Stage")
};

UENUM(BlueprintType)
enum class EStageState : uint8
{
	ESS_Normal UMETA(Displayname = "Normal"),
	ESS_Anomaly UMETA(Displayname = "Anomaly")
};

UENUM(BlueprintType)
enum class EAnomalyType : uint8
{
	EAT_None UMETA(Displayname = "None"),
	EAT_RenewaFrame UMETA(Displayname = "Renewa Frame"),
	EAT_NotKommyChase UMETA(Displayname = "NotKommy Chasing"),
	EAT_RenewaQuiz UMETA(Displayname = "Renewa Quiz"),
	EAT_ChangeStandee UMETA(Displayname = "Change Standee"),
	EAT_SongPyeon UMETA(Displayname = "Songpyeon"),
	EAT_BurningTree UMETA(Displayname = "Burning Tree"),
	EAT_LightOff UMETA(Displayname = "Light Off"),
	EAT_RedLight UMETA(Displayname = "Red Light"),
	EAT_MiroAppeared UMETA(Displayname = "Miro Appeared"),
	EAT_MirrorUpsideDown UMETA(Displayname = "Mirror Upside Down"),
	EAT_MAX UMETA(Hidden)
};

struct FAnomalyTypeHelper
{
	static bool RequiresDefeat(EAnomalyType Type)
	{
		switch (Type)
		{
			case EAnomalyType::EAT_RenewaQuiz:
			case EAnomalyType::EAT_RedLight:
				return true;

			default:
				return false;
		}
	}
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(Displayname = "Idle"),
	ECS_Chasing UMETA(Displayname = "Chasing"),
	ECS_Dialogue UMETA(Displayname = "Dialogue"),
	ECS_Dead UMETA(Displayname = "Dead"),
	ECS_Sit UMETA(Displayname = "Sit"),
};

UENUM(BlueprintType)
enum class ECutsceneName : uint8
{
	ECN_None UMETA(DisplayName = "None"),
	ECN_NotKommy UMETA(DisplayName = "NotKommy"),
	ECN_RenewaQuiz UMETA(DisplayName = "Renewa Quiz"),
	ECN_RedLight UMETA(DisplayName = "Red Light"),
	ECN_TestA_001 UMETA(DisplayName = "TestA_001"),

};

UENUM(BlueprintType)
enum class ECutsceneType : uint8
{
	ECT_Normal UMETA(DisplayName = "Normal"),
	ECT_Death UMETA(DisplayName = "Death")
};

UENUM(BlueprintType)
enum class EAnomalyStatus : uint8
{
	EAS_NotSeen UMETA(DisplayName = "Not Seen"),
	EAS_SeenButNotFound UMETA(DisplayName = "Seen but not Found"),
	EAS_Found UMETA(DisplayName = "Found")
};

UENUM(BlueprintType)
enum class ERedLightStageStatus : uint8
{
	ERSS_Entered UMETA(DisplayName = "Entered"),
	ERSS_OnPlaying UMETA(DisplayName = "On Playing"),
	ERSS_TimeOut UMETA(DisplayName = "Time Out"),
	ERSS_RedLightMoved UMETA(DisplayName = "Red Light Moved"),
	ERSS_PlayDeathScene UMETA(DisplayName = "Play Death Scene"),
	ERSS_Pass UMETA(DisplayName = "Pass")
};


UENUM(BlueprintType)
enum class EMainMenuStatus : uint8
{
	EMMS_Intro UMETA(DisplayName = "Intro"),
	EMMS_MainMenu UMETA(DisplayName = "Main Menu"),
	EMMS_StartGame UMETA(DisplayName = "Start Game"),
	EMMS_Collection UMETA(DisplayName = "Collection"),
	EMMS_CollectionDetail UMETA(DisplayName = "Collection Detail"),
	EMMS_Setting UMETA(DisplayName = "Setting")
};


UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	EGP_Normal UMETA(DisplayName = "Normal"),
	EGP_CutScene UMETA(DisplayName = "CutScene"),
	EGP_PlayMedia UMETA(DisplayName = "Play Media"),
	EGP_Dialogue UMETA(DisplayName = "Dialogue"),
	EGP_Monologue UMETA(DisplayName = "Monologue"),
};

UENUM(BlueprintType)
enum class EPauseStatus : uint8
{
	EPS_NotPaused UMETA(DisplayName = "Not Paused"),
	EPS_PausedMain UMETA(DisplayName = "Paused Main"),
	EPS_Collection UMETA(DisplayName = "Collection"),
	EPS_Setting UMETA(DisplayName = "Setting"),
};

UENUM(BlueprintType)
enum class EDialogueMode : uint8
{
	EDM_NotOnDialogue UMETA(DisplayName = "Not On Dialogue"),
	EDM_Dialogue UMETA(DisplayName = "Dialogue"),
	EDM_Monologue UMETA(DisplayName = "Monologue"),
};

USTRUCT()
struct FAnomalyEntry
{
	GENERATED_BODY()

	UPROPERTY()
	EAnomalyType Type = EAnomalyType::EAT_None;

	UPROPERTY()
	EAnomalyStatus Status = EAnomalyStatus::EAS_NotSeen;
};