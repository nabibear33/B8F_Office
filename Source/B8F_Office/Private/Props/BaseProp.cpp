

#include "Props/BaseProp.h"
#include "GameManager/StageManager.h"
#include "Kismet/GameplayStatics.h"

ABaseProp::ABaseProp()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;
}

void ABaseProp::BeginPlay()
{
	Super::BeginPlay();

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &ABaseProp::OnStageStart);
	}
	
}

void ABaseProp::OnStageStart(EAnomalyType AnomalyType)
{

}

void ABaseProp::SetNormal()
{
}

