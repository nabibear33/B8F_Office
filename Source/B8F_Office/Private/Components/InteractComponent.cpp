// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/InteractWidget.h"
#include "HUD/MainHUD.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractableArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractableArea"));
	InteractableArea->SetSphereRadius(150.f);
}

void UInteractComponent::SetInteractEnabled()
{
	bCanOwnerInteract = true;

	InteractableArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UInteractComponent::SetInteractDisabled()
{
	bCanOwnerInteract = false;

	InteractableArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UInteractComponent::OnRegister()
{
	Super::OnRegister();

	// TODO: BUGBUG: Work around the 'Template Mismatch during attachment. Attaching instanced component to template component.' problem.
	// Remove after Epic acknowledges and fixes this long-standing bug or provides guidance.
	// The constructor-initialized components, upon non-CDO instantiation/initialization, are getting CDO references for their attached parents, instead of instance references.
	// A work-around...
	//     - Use SetupAttachment(), per usual in the constructor to establish the parent-child relationship for CDOs.
	//     - Use AttachToComponent() to override those errant CDO references with instance references, in your USceneComponent::OnRegister() override.
	InteractableArea->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractableArea->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnBeginOverlap);
	InteractableArea->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnEndOverlap);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainCharacter* Player = Cast<AMainCharacter>(PC->GetPawn());
	if (Player)
	{
		OnInteractableUpdated.AddDynamic(Player, &AMainCharacter::OnInteractableUpdated);
		OnInteractableLeft.AddDynamic(Player, &AMainCharacter::OnInteractableLeft);
	}

	AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
	if (HUD)
	{
		OnInteractableUpdated.AddDynamic(HUD, &AMainHUD::OnInteractableUpdated);
		OnInteractableLeft.AddDynamic(HUD, &AMainHUD::OnInteractableLeft);
	}
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractComponent::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CanOwnerInteract()) return;
	
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (!Player) return;
	UE_LOG(LogTemp, Warning, TEXT("[Interactable Component] [%s] detected Player"), *GetOwner()->GetName());

	OnInteractableUpdated.Broadcast(GetOwner(), InteractableArea->GetComponentLocation(), InteractText);
}

void UInteractComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!CanOwnerInteract()) return;

	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (!Player) return;

	OnInteractableLeft.Broadcast(GetOwner());
}
