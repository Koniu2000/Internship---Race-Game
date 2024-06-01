

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "FinishLine.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AFinishLine : public AObstacle
{
	GENERATED_BODY()


public:
	AFinishLine();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BoardMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FinishLineMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MetalTabMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MetalTabBottomMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> SecondBoxComponent;

	
};
