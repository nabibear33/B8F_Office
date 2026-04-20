#pragma once

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
	EAT_Normal UMETA(Displayname = "Normal"),
	EAT_RenewaFrame UMETA(Displayname = "Renewa Frame"),
	EAT_NotKommyChase UMETA(Displayname = "NotKommy Chasing"),
	EAT_RenewaQuiz UMETA(Displayname = "Renewa Quiz"),
	EAT_ChangeStandee UMETA(Displayname = "Change Standee"),
	EAT_SongPyeon UMETA(Displayname = "Songpyeon"),
	EAT_BurningTree UMETA(Displayname = "Burning Tree"),
	EAT_MAX UMETA(Hidden)
};

struct FAnomalyTypeHelper
{
	static bool RequiresDefeat(EAnomalyType Type)
	{
		switch (Type)
		{
			case EAnomalyType::EAT_RenewaQuiz:
				return true;

			case EAnomalyType::EAT_NotKommyChase:
			case EAnomalyType::EAT_Normal:
			case EAnomalyType::EAT_RenewaFrame:
			case EAnomalyType::EAT_ChangeStandee:
			case EAnomalyType::EAT_SongPyeon:
			case EAnomalyType::EAT_BurningTree:
			default:
				return false;
		}
	}
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(Displayname = "Idle"),
	ECS_Chasing UMETA(Displayname = "Chasing")
};

UENUM(BlueprintType)
enum class EDeathSceneType : uint8
{
	EDS_None UMETA(DisplayName = "None"),
	EDS_NotKommy UMETA(DisplayName = "NotKommy")
};

UENUM(BlueprintType)
enum class EAnomalyStatus : uint8
{
	EAS_NotSeen UMETA(DisplayName = "Not Seen"),
	EAS_SeenButNotFound UMETA(DisplayName = "Seen but not Found"),
	EAS_Found UMETA(DisplayName = "Found")
};