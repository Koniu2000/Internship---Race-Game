// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarBase.h"
#include "AICar.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AAICar : public ACarBase
{
	GENERATED_BODY()
	
public:
	AAICar();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void BotWon();

	float CalcSteering();
	float CalcTopSpeed();
	void CalcThrottle(float TopSpeed);

	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	FVector GetClosestLocationToPath(AAICarPath* ActorPath, float AdditionalDistance);

	float ForwardSpeed;
};
