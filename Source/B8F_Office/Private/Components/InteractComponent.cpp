// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/InteractWidget.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractableArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractableArea"));
	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
	// UE_LOG(LogTemp, Warning, TEXT("[InteractComponent] this: %s"), *GetName());
	// UE_LOG(LogTemp, Warning, TEXT("[InteractComponent] InteractableArea outer: %s"), *InteractableArea->GetOuter()->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("[InteractComponent] InteractableArea attach parent: %s"),InteractableArea->GetAttachParent() ? *InteractableArea->GetAttachParent()->GetName() : TEXT("NULL"));

}

void UInteractComponent::SetInteractEnabled()
{
	bIsOwnerInteractable = true;

	InteractableArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UInteractComponent::SetInteractDisabled()
{
	bIsOwnerInteractable = false;

	InteractableArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// For the case when calling SetInteractDisabled() while player is still in the interactable area, we need to hide the widget as well.
	InteractWidgetComponent->SetVisibility(false);
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
	InteractWidgetComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	InteractWidgetComponent->SetVisibility(false);
	InteractWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractWidgetComponent->SetTwoSided(true);
	InteractWidgetComponent->SetDrawSize(FVector2D(100.f, 100.f));
	InteractWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("[InteractComponent] BeginPlay - InteractableArea attach parent: %s"), InteractableArea->GetAttachParent() ? *InteractableArea->GetAttachParent()->GetName() : TEXT("NULL"));

	if (InteractWidgetClass)
	{
		InteractWidgetComponent->SetWidgetClass(InteractWidgetClass);
		InteractWidgetComponent->SetVisibility(false);
	}

	IInteractable* Interactable = Cast<IInteractable>(GetOwner());
	InteractWidget = Cast<UInteractWidget>(InteractWidgetComponent->GetWidget());
	if (InteractWidget && Interactable)
	{
		InteractWidget->SetInteractContentText(Interactable->GetInteractHintText());
	}


	InteractableArea->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnBeginOverlap);
	InteractableArea->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnEndOverlap);
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractComponent::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsOwnerInteractable()) return;
	
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (!Player) return;

	UE_LOG(LogTemp, Warning, TEXT("[%s] Player detected: %s"), *GetOwner()->GetName(), *Player->GetName());

	InteractWidgetComponent->SetVisibility(true);

	OnInteractableEntered.Broadcast(GetOwner(), Player);

}

void UInteractComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsOwnerInteractable()) return;

	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (!Player) return;

	InteractWidgetComponent->SetVisibility(false);

	OnInteractableLeft.Broadcast(GetOwner(), Player);
}
