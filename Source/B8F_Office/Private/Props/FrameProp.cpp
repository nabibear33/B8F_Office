

#include "Props/FrameProp.h"

AFrameProp::AFrameProp()
{
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);
}

void AFrameProp::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialInstance = FrameMesh->CreateDynamicMaterialInstance(0);
}

void AFrameProp::ChangeImage(int32 ImageIndex)
{
	if (!DynamicMaterialInstance || !ImageList.IsValidIndex(ImageIndex)) return;

	DynamicMaterialInstance->SetTextureParameterValue(TEXT("ActivatedTexture"), ImageList[ImageIndex]);
}

void AFrameProp::OnStageStart(EAnomalyType AnomalyType)
{
	Super::OnStageStart(AnomalyType);

	switch (AnomalyType)
	{
		case EAnomalyType::EAT_RenewaFrame:
			UE_LOG(LogTemp, Warning, TEXT("Anomaly Image Change Triggered"));
			ChangeImage(1);
			break;

		default:
			SetNormal();
			UE_LOG(LogTemp, Warning, TEXT("Normal Image Change Triggered"));
			break;
	}
}

void AFrameProp::SetNormal()
{
	ChangeImage(0);
}
