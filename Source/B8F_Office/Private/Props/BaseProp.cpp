

#include "Props/BaseProp.h"
#include "GameManager/StageManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InteractComponent.h"

ABaseProp::ABaseProp()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

UInteractComponent* ABaseProp::GetInteractComponent()
{
	return InteractComponent;
}

void ABaseProp::BeginPlay()
{
	Super::BeginPlay();

	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &ABaseProp::OnStageStart);
	}

	InteractComponent->SetInteractEnabled(bIsInteractable);
}

void ABaseProp::OnStageStart(EAnomalyType AnomalyType)
{
}

void ABaseProp::SetNormal()
{
}

