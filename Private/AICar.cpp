


#include "AICar.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "LevelGameMode.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "AICarPath.h"


AAICar::AAICar()
{
	CarMovementComponent->EngineSetup.MaxRPM = 7500.f;
}

void AAICar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForwardSpeed = CarMovementComponent->GetForwardSpeed() * 0.036;

	if (!MovementStopped)
	{
		CarMovementComponent->SetSteeringInput(CalcSteering());
		CalcThrottle(CalcTopSpeed());
	}
}

void AAICar::BeginPlay()
{
	Super::BeginPlay();
}

float AAICar::CalcSteering()
{
	float AdditionalDistance = UKismetMathLibrary::MapRangeClamped(ForwardSpeed, 50.f, 150.f, 1000.f, 3000.f);

	FVector ClosestLocation = GetClosestLocationToPath(ActualPath, AdditionalDistance);
	FRotator RotatorToPath = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ClosestLocation);
	FRotator CarRotator = RotatorToPath - GetActorRotation();

	double TurnAngle = 180.0;
	CarRotator.Yaw = FMath::Wrap(CarRotator.Yaw, -TurnAngle, TurnAngle);

	double SteeringInput = UKismetMathLibrary::MapRangeClamped(CarRotator.Yaw, -10.0, 10.0, -1.0, 1.0);

	return SteeringInput;
}

float AAICar::CalcTopSpeed()
{
	float AdditionalDistance = UKismetMathLibrary::MapRangeClamped(ForwardSpeed, 50.f, 150.f, 3000.f, 9000.f);

	FVector ClosestLocation = GetClosestLocationToPath(ActualPath, AdditionalDistance);
	FRotator RotatorToPath = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ClosestLocation);
	FRotator CarRotator = RotatorToPath - GetActorRotation();

	double TurnAngle = 180.0;
	CarRotator.Yaw = FMath::Wrap(CarRotator.Yaw, -TurnAngle, TurnAngle);

	double TopSpeed = UKismetMathLibrary::MapRangeClamped(UKismetMathLibrary::Abs(CarRotator.Yaw), 0.0, 40.0, 150.0, 50.0);

	return TopSpeed;
}

void AAICar::CalcThrottle(float TopSpeed)
{
	TopSpeed = CalcTopSpeed();
	if (ForwardSpeed >= TopSpeed)
	{
		CarMovementComponent->SetBrakeInput(1.f);
		CarMovementComponent->SetThrottleInput(0.f);
	}
	else
	{
		CarMovementComponent->SetBrakeInput(0.f);
		CarMovementComponent->SetThrottleInput(1.f);
	}
}

void AAICar::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	RefreshLap();
	BotWon();
}

FVector AAICar::GetClosestLocationToPath(AAICarPath* ActorPath, float AdditionalDistance)
{
	USplineComponent* SplinePath = ActorPath->GetPath();
	float Distance = SplinePath->GetDistanceAlongSplineAtLocation(GetActorLocation(), ESplineCoordinateSpace::World);

	FVector ClosestLocation = SplinePath->GetLocationAtDistanceAlongSpline(Distance + AdditionalDistance, ESplineCoordinateSpace::World);

	return ClosestLocation;
}

void AAICar::BotWon()
{
	if (GameMode->GetMapLaps() == CurrentLap)
	{
		GameMode->SetGameWonByBot();
	}
}
