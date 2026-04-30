#pragma once

#include "Types.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EGS_OnStage UMETA(Displayname = "On Stage"),
	EGS_IntermediateStage UMETA(Displayname = "Intermediate Stage")
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
	ECS_Dying UMETA(Displayname = "Dying")
};

UENUM(BlueprintType)
enum class EDeathSceneType : uint8
{
	EDS_None UMETA(DisplayName = "None"),
	EDS_NotKommy UMETA(DisplayName = "NotKommy"),
	EDS_RenewaQuiz UMETA(DisplayName = "Renewa Quiz"),
	EDS_RedLight UMETA(DisplayName = "Red Light")
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
enum class EProgressType : uint8
{
	EPT_Normal UMETA(DisplayName = "Normal"),
	EPT_CutScene UMETA(DisplayName = "CutScene"),
	EPT_PlayMedia UMETA(DisplayName = "Play Media"),
	EPT_Dialogue UMETA(DisplayName = "Dialogue"),
	EPT_Monologue UMETA(DisplayName = "Monologue"),
};

USTRUCT()
struct FMainStageStatus
{
	GENERATED_BODY()

	int CurrentFloor;

	TMap<EAnomalyType, EAnomalyStatus> AnomalyRecord;
};