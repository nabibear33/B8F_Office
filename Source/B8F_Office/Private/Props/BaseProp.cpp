

#include "Props/BaseProp.h"
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
}

void ABaseProp::AdvanceProgress(FName Name)
{
	OnGameProgressUpdated.Broadcast(Name);
}

