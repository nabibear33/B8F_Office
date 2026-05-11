
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props/AnomalyProp.h"
#include "TextureChangeableProp.generated.h"

UCLASS()
class B8F_OFFICE_API ATextureChangeableProp : public AAnomalyProp
{
	GENERATED_BODY()
	
public:	
	ATextureChangeableProp();

protected:
	virtual void BeginPlay() override;

	void ChangeImage(int32 ImageIndex);

private:	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UTexture2D>> TextureList;

	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	void OnStageStart(EAnomalyType AnomalyType) override;
	void SetNormal() override;
};
