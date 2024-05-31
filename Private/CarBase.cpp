// Copyright 2023 Teyon. All Rights Reserved.


#include "CarBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelGameMode.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "FrontChaosVehicleWheel.h"
#include "BackChaosVehicleWheel.h"
#include "AICarPath.h"
#include "CheckpointTriggerBox.h"


ACarBase::ACarBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(1.f, 1.f, 1.f));

	CarBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarBody"));
	CarBody->SetupAttachment(RootComponent);

	//Engine
	CarEngine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarEngine"));
	CarEngine->SetupAttachment(CarBody);

	//Interior
	CarInterior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarInterior"));
	CarInterior->SetupAttachment(CarBody);

	CarNet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarNet"));
	CarNet->SetupAttachment(CarBody);

	InteriorSeat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteriorSeat"));
	InteriorSeat->SetupAttachment(CarBody);

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitConsole"));
	CockpitConsole->SetupAttachment(InteriorSeat);

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(InteriorSeat);

	PedalAcceleration = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalAcceleration"));
	PedalAcceleration->SetupAttachment(InteriorSeat);

	PedalBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalBrake"));
	PedalBrake->SetupAttachment(InteriorSeat);

	//Wheels
	FrontRightBreakDisc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightBreakDisc"));
	FrontRightBreakDisc->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontRightBrakeDiscSocket");

	FrontLeftBreakDisc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftBreakDisc"));
	FrontLeftBreakDisc->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontLeftBrakeDiscSocket");

	BackRightBreakDisc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightBreakDisc"));
	BackRightBreakDisc->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackRightBrakeDiscSocket");

	BackLeftBreakDisc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftBreakDisc"));
	BackLeftBreakDisc->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackLeftBrakeDiscSocket");

	FrontRightCaliper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightCaliper"));
	FrontRightCaliper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontRightCaliperSocket");

	FrontLeftCaliper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftCaliper"));
	FrontLeftCaliper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontLeftCaliperSocket");

	BackRightCaliper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightCaliper"));
	BackRightCaliper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackRightCaliperSocket");

	BackLeftCaliper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftCaliper"));
	BackLeftCaliper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackLeftCaliperSocket");

	FrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightWheel"));
	FrontRightWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontRightWheelSocket");

	FrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftWheel"));
	FrontLeftWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontLeftWheelSocket");

	BackRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightWheel"));
	BackRightWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackRightWheelSocket");

	BackLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftWheel"));
	BackLeftWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackLeftWheelSocket");

	//Exterior
	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "RightDoorSocket");

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "LeftDoorSocket");

	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRight"));
	FenderRight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "RightFenderSocket");

	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeft"));
	FenderLeft->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "LeftFenderSocket");

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	FrontBumper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "FrontBumperSocket");

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontHood"));
	FrontHood->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "HoodSocket");

	BackBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackBoot"));
	BackBoot->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackBootSocket");

	BackSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackSpoiler"));
	BackSpoiler->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "SpoilerSocket");

	BackBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackBumper"));
	BackBumper->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BackBumperSocket");

	BackDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackDiffuser"));
	BackDiffuser->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "DiffuserSocket");

	WingRightMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingRightMirror"));
	WingRightMirror->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "RightWingMirrorSocket");

	WingLeftMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingLeftMirror"));
	WingLeftMirror->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "LeftWingMirrorSocket");
	
	Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));
	Window->SetupAttachment(CarBody);

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wiper"));
	Wiper->SetupAttachment(CarBody);

	BackRightLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("BackRightLight"));
	BackRightLight->SetupAttachment(BackBumper);
	BackRightLight->SetIntensity(1250.f);
	BackRightLight->SetLightColor(FLinearColor::Red);

	BackLeftLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("BackLeftLight"));
	BackLeftLight->SetupAttachment(BackBumper);
	BackLeftLight->SetIntensity(1250.f);
	BackLeftLight->SetLightColor(FLinearColor::Red);

	CarMovementComponent = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	if (CarMovementComponent)
	{
		CarMovementComponent->WheelSetups.SetNum(4);

		CarMovementComponent->WheelSetups[0].WheelClass = UFrontChaosVehicleWheel::StaticClass();
		CarMovementComponent->WheelSetups[0].BoneName = FName("suspension_front_right");

		CarMovementComponent->WheelSetups[1].WheelClass = UFrontChaosVehicleWheel::StaticClass();
		CarMovementComponent->WheelSetups[1].BoneName = FName("suspension_front_left");

		CarMovementComponent->WheelSetups[2].WheelClass = UBackChaosVehicleWheel::StaticClass();
		CarMovementComponent->WheelSetups[2].BoneName = FName("suspension_back_right");

		CarMovementComponent->WheelSetups[3].WheelClass = UBackChaosVehicleWheel::StaticClass();
		CarMovementComponent->WheelSetups[3].BoneName = FName("suspension_back_left");

		CarMovementComponent->EngineSetup.MaxRPM = 7000.f;
		CarMovementComponent->EngineSetup.EngineIdleRPM = 850.f;
		CarMovementComponent->EngineSetup.EngineRevUpMOI = 0.1f;
		CarMovementComponent->EngineSetup.EngineRevDownRate = 4000.0f;

		CarMovementComponent->TransmissionSetup.ForwardGearRatios.SetNum(6);
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[0] = 3.82f;
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[1] = 2.2f;
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[2] = 1.52f;
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[3] = 1.22f;
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[4] = 1.02f;
		CarMovementComponent->TransmissionSetup.ForwardGearRatios[5] = 0.84f;

		CarMovementComponent->TransmissionSetup.FinalRatio = 3.9f;

		CarMovementComponent->TransmissionSetup.ReverseGearRatios.SetNum(1);
		CarMovementComponent->TransmissionSetup.ReverseGearRatios[0] = 1.f;
	}

	MovementStopped = true;
	StartTime = 3.f;
}

void ACarBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACarBase::OnBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ACarBase::CanDrive, 3.0f, false);

	GameMode = Cast<ALevelGameMode>(GetWorld()->GetAuthGameMode());
	NumberOfCheckpoints = GameMode->GetNumOfCheckPoints();

	ActualPath = Cast<AAICarPath>(UGameplayStatics::GetActorOfClass(GetWorld(), AAICarPath::StaticClass()));
}

void ACarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);;
}

float ACarBase::GetDistanceAlongSpline() const
{
	if (ActualPath)
	{
		return ActualPath->GetPath()->GetDistanceAlongSplineAtLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	}
	return 0.0f;
}

void ACarBase::CanDrive()
{
	MovementStopped = false;
}

void ACarBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACheckpointTriggerBox* TriggerBox = Cast<ACheckpointTriggerBox>(OtherActor);

	if (TriggerBox && TriggerBox->GetCheckpointID() - 1 == CurrentCheckpointID)
	{
		CurrentCheckpointID++;
	}
}

bool ACarBase::CheckIfLap()
{
	return NumberOfCheckpoints == CurrentCheckpointID;
}

void ACarBase::RefreshLap()
{
	if (CheckIfLap())
	{
		CurrentCheckpointID = 0;
		CurrentLap++;
	}
}

