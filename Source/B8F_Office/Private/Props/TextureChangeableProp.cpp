

#include "Props/TextureChangeableProp.h"

ATextureChangeableProp::ATextureChangeableProp()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void ATextureChangeableProp::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialInstance = MeshComponent->CreateDynamicMaterialInstance(0);
}

void ATextureChangeableProp::ChangeImage(int32 ImageIndex)
{
	if (!DynamicMaterialInstance || !TextureList.IsValidIndex(ImageIndex)) return;

	DynamicMaterialInstance->SetTextureParameterValue(TEXT("ActivatedTexture"), TextureList[ImageIndex]);
}

void ATextureChangeableProp::OnStageStart(EAnomalyType AnomalyType)
{
	Super::OnStageStart(AnomalyType);

	if (AnomalyType == CorrespondingAnomalyType)
	{
		ChangeImage(1);
	}
	else
	{
		SetNormal();
	}
}

void ATextureChangeableProp::SetNormal()
{
	ChangeImage(0);
}
