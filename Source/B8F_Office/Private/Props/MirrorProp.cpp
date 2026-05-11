// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/MirrorProp.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"


AMirrorProp::AMirrorProp()
{
	PrimaryActorTick.bCanEverTick = true;

	MirrorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorMesh"));
	MirrorMesh->SetupAttachment(RootComponent);
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(RootComponent);
}

void AMirrorProp::BeginPlay()
{
	Super::BeginPlay();

	if (RenderTarget)
	{
		SceneCapture->TextureTarget = RenderTarget;
	}

	MID = MirrorMesh->CreateAndSetMaterialInstanceDynamic(0);
	MID->SetTextureParameterValue(TEXT("MirrorTexture"), RenderTarget);
}

void AMirrorProp::OnStageStart(EAnomalyType AnomalyType)
{
	if (AnomalyType == EAnomalyType::EAT_MirrorUpsideDown)
	{
		MID->SetVectorParameterValue(TEXT("UV_Tiling"), FLinearColor(1.f, -1.f, 0.f, 0.f));

	}
	else
	{
		MID->SetVectorParameterValue(TEXT("UV_Tiling"), FLinearColor(1.f, 1.f, 0.f, 0.f));
	}
}

void AMirrorProp::Tick(float Deltatime)
{
	// Get Reflection vector
	FVector MirrorNormal = MirrorMesh->GetUpVector();
	FVector MirrorPos = MirrorMesh->GetComponentLocation();
	ACharacter* Character = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UCameraComponent* Camera = Character->FindComponentByClass<UCameraComponent>();
	FVector CameraPos = Camera->GetComponentLocation();
	FVector ToCamera = (CameraPos - MirrorPos);
	FVector Reflected = ToCamera - 2.f * FVector::DotProduct(ToCamera, MirrorNormal) * MirrorNormal;
	SceneCapture->SetWorldLocation(MirrorPos + Reflected);
	SceneCapture->SetWorldRotation((MirrorPos - SceneCapture->GetComponentLocation()).Rotation());

	// clip objects for the case of SceneCapture positioned behind the wall
	SceneCapture->bEnableClipPlane = true;
	SceneCapture->ClipPlaneBase = MirrorPos;
	SceneCapture->ClipPlaneNormal = MirrorNormal;

	float Distance = FVector::Distance(CameraPos, MirrorPos);
	float MirrorHalfSize = 100.f;
	float FOV = FMath::RadiansToDegrees(2.f * FMath::Atan(MirrorHalfSize / Distance));
	SceneCapture->FOVAngle = FMath::Clamp(FOV, 10.f, 160.f);
	
	/*

	// ��ġ Ȯ��
	DrawDebugSphere(
		GetWorld(),
		SceneCapture->GetComponentLocation(),
		20.f,          // ������
		12,            // ���׸�Ʈ
		FColor::Orange,
		false, -1.f, 0, 1.f
	);

	// SceneCapture �� MirrorPos ���� Ȯ��
	DrawDebugDirectionalArrow(
		GetWorld(),
		SceneCapture->GetComponentLocation(),
		MirrorPos,
		20.f,
		FColor::Yellow,
		false, -1.f, 0, 2.f
	);

	DrawDebugDirectionalArrow(
		GetWorld(),
		MirrorPos,                    // ������
		MirrorPos + ToCamera,         // ����
		20.f,                         // ȭ��ǥ ũ��
		FColor::Green,                // ����
		false,                        // ���� ����
		-1.f,                         // ���� �ð� (-1 = �� ������)
		0,                            // depth priority
		2.f                           // �β�
	);

	DrawDebugDirectionalArrow(GetWorld(), MirrorPos, MirrorPos + Reflected, 20.f, FColor::Orange, false, -1.f, 0, 2.f);
	DrawDebugDirectionalArrow(GetWorld(), MirrorPos, MirrorPos + MirrorNormal * 100.f, 20.f, FColor::Blue, false, -1.f, 0, 2.f);

	DrawDebugDirectionalArrow(GetWorld(), MirrorPos, MirrorPos + MirrorMesh->GetForwardVector() * 100.f, 20.f, FColor::Red, false, -1.f, 0, 2.f);
	DrawDebugDirectionalArrow(GetWorld(), MirrorPos, MirrorPos + MirrorMesh->GetRightVector() * 100.f, 20.f, FColor::Green, false, -1.f, 0, 2.f);
	DrawDebugDirectionalArrow(GetWorld(), MirrorPos, MirrorPos + MirrorMesh->GetUpVector() * 100.f, 20.f, FColor::Blue, false, -1.f, 0, 2.f);
	*/

}
