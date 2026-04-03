
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props/BaseProp.h"
#include "FrameProp.generated.h"

UCLASS()
class B8F_OFFICE_API AFrameProp : public ABaseProp
{
	GENERATED_BODY()
	
public:	
	AFrameProp();

protected:
	virtual void BeginPlay() override;

	void ChangeImage(int32 ImageIndex);

private:	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> FrameMesh;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UTexture2D>> ImageList;

	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	void OnStageStart(EAnomalyType AnomalyType) override;
	void SetNormal() override;
};
