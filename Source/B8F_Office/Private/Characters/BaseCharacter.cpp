

#include "Characters/BaseCharacter.h"
#include "GameManager/StageManager.h"
#include "Components/InteractComponent.h"
#include "Characters/MainCharacter.h"
#include "Controllers/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AStageManager* StageManager = Cast<AStageManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStageManager::StaticClass()));
	if (StageManager)
	{
		StageManager->OnStageStart.AddDynamic(this, &ABaseCharacter::OnStageStart);
	}

	if (!bIsInteractable)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] bIsInteractable false → SetInteractEnabled(false)"), *GetName());
		InteractComponent->SetInteractEnabled(false);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FText ABaseCharacter::GetInteractHintText()
{
	return FText(FText::FromString(TEXT("Interact")));
}

void ABaseCharacter::OnStageStart(EAnomalyType AnomalyType)
{
}

void ABaseCharacter::SetNormal()
{
}

