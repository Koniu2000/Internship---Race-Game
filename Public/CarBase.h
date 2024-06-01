

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h" 
#include "InputActionValue.h"
#include "CarBase.generated.h"

class UBoxComponent;
class UPointLightComponent;
class UChaosWheeledVehicleMovementComponent;
class ALevelGameMode;
class AAICarPath;

UCLASS()
class PRAKTYKI_API ACarBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	ACarBase();
	virtual void Tick(float DeltaTime) override;
	float GetDistanceAlongSpline() const;

	FORCEINLINE int GetCurrentLap() const { return CurrentLap; }
	FORCEINLINE int GetCurrentCheckpoint() const { return CurrentCheckpointID; }

protected:
	virtual void BeginPlay() override;

	bool CheckIfLap();
	virtual void RefreshLap();
	void CanDrive();

	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int NumberOfCheckpoints;

	UPROPERTY(BlueprintReadOnly)
	int CurrentLap;

	UPROPERTY(BlueprintReadOnly)
	bool MovementStopped;

	UPROPERTY(VisibleAnywhere)
	int CurrentCheckpointID;

	FTimerHandle MovementTimerHandle;
	float StartTime;

	TObjectPtr<ALevelGameMode> GameMode;
	TObjectPtr<UChaosWheeledVehicleMovementComponent> CarMovementComponent;
	TObjectPtr<AAICarPath> ActualPath;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> CarBody;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> CarEngine;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> CockpitConsole;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> DoorLeft;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> DoorRight;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontRightWheel;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontLeftWheel;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackRightWheel;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackLeftWheel;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> Window;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FenderRight;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FenderLeft;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontRightBreakDisc;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontLeftBreakDisc;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackRightBreakDisc;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackLeftBreakDisc;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontBumper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontHood;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontRightCaliper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> FrontLeftCaliper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackRightCaliper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackLeftCaliper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> CarInterior;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> CarNet;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> PedalAcceleration;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> PedalBrake;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackBoot;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackBumper;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackDiffuser;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> BackSpoiler;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> InteriorSeat;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> SteeringWheel;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> WingRightMirror;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> WingLeftMirror;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> Wiper;

	UPROPERTY(VisibleAnywhere, Category = Lights)
	TObjectPtr<UPointLightComponent> BackRightLight;

	UPROPERTY(VisibleAnywhere, Category = Lights)
	TObjectPtr<UPointLightComponent> BackLeftLight;
};
