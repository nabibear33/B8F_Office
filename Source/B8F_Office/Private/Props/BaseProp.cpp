

#include "Props/BaseProp.h"
#include "Components/InteractComponent.h"
#include "GameInstances/GameSubsystem.h"

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

	UGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (Subsystem)
	{
		OnGameProgressUpdated.AddDynamic(Subsystem, &UGameSubsystem::OnGameProgressUpdated);
	}

	InteractComponent->SetInteractEnabled();
}

void ABaseProp::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("[Base Prop] Interact"));
	AdvanceProgress(LinkedProgressName);

	// later add logic for dialogue
}

void ABaseProp::AdvanceProgress(FName Name)
{
	if (Name == NAME_None) return;
	OnGameProgressUpdated.Broadcast(Name);
}

