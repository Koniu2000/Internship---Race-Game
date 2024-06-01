

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICarPath.generated.h"

class USplineComponent;

UCLASS()
class PRAKTYKI_API AAICarPath : public AActor
{
	GENERATED_BODY()
	
public:	
	AAICarPath();
	USplineComponent* GetPath() const;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> Path;

};
