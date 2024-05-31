// Copyright 2023 Teyon. All Rights Reserved.


#include "PlayerCar.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"

APlayerCar::APlayerCar()
{
	Camera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	Camera1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BehindCarGameplayCameraFar");

	Camera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));
	Camera2->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "BehindCarGameplayCameraNear");

	Camera3 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera3"));
	Camera3->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "CarInteriorGameplayCamera");

	CurrentLapTime = 0.f;
	BestLapTime = 0.f;
	CameraID = 0;

	InSlowingBox = false;
	ApplySlow = false;
}

void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCar::MoveForward);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &APlayerCar::MoveForward);
		EnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &APlayerCar::MoveBackward);
		EnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Completed, this, &APlayerCar::MoveBackward);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &APlayerCar::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &APlayerCar::Steering);
		EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Triggered, this, &APlayerCar::HandBrake);
		EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &APlayerCar::HandBrake);
		EnhancedInputComponent->BindAction(CameraChangeAction, ETriggerEvent::Triggered, this, &APlayerCar::ChangeCamera);
	}
}

void APlayerCar::ResetLap()
{
	CurrentLap = 0;
}

void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MovementStopped)
	{
		CurrentLapTime = GetWorld()->GetTimeSeconds() - StartTime;
	}

	RefreshTime();
	RefreshLap();
	SlowDown();
}

void APlayerCar::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CarMappingContext, 0);
		}
	}

	CurrentCheckpointID = 0;
	CurrentLap = 0;
}

void APlayerCar::MoveForward(const FInputActionValue& Value)
{
	const FVector MoveValue = Value.Get<FVector>();

	if (!MovementStopped)
	{
		if (CarMovementComponent)
		{
			CarMovementComponent->SetThrottleInput(MoveValue.X);
		}
	}
}

void APlayerCar::MoveBackward(const FInputActionValue& Value)
{
	const FVector BrakeValue = Value.Get<FVector>();

	if (!MovementStopped)
	{
		if (CarMovementComponent)
		{
			CarMovementComponent->SetBrakeInput(BrakeValue.X);
			if (BrakeValue.X > 0)
			{
				BackRightLight->SetIntensity(7500.f);
				BackLeftLight->SetIntensity(7500.f);
			}
			else
			{
				BackRightLight->SetIntensity(1250.f);
				BackLeftLight->SetIntensity(1250.f);
			}
		}
	}
}

void APlayerCar::Steering(const FInputActionValue& Value)
{
	const FVector SteeringValue = Value.Get<FVector>();

	if (CarMovementComponent)
	{
		CarMovementComponent->SetSteeringInput(SteeringValue.X * 10.f);
	}
}

void APlayerCar::HandBrake(const FInputActionValue& Value)
{
	const bool HandBrakeValue = Value.Get<bool>();

	if (CarMovementComponent && !InSlowingBox)
	{
		CarMovementComponent->SetHandbrakeInput(HandBrakeValue);
	}
}

void APlayerCar::ChangeCamera(const FInputActionValue& Value)
{
	const bool CameraChangeValue = Value.Get<bool>();

	CameraID++;

	if (CameraID > 2)
	{
		CameraID = 0;
	}

	switch (CameraID)
	{
	case 0:
		Camera1->Activate();
		Camera3->Deactivate();
		break;
	case 1:
		Camera2->Activate();
		Camera1->Deactivate();
		break;
	case 2:
		Camera2->Deactivate();
		Camera3->Activate();
		break;
	}
}

void APlayerCar::RefreshTime()
{
	if (CheckIfLap())
	{
		LapTimes.Add(CurrentLapTime);
		if (BestLapTime == 0.f || CurrentLapTime < BestLapTime)
		{
			BestLapTime = CurrentLapTime;
		}
		CurrentLapTime = 0.f;
		RefreshLap();
		StartTime = GetWorld()->GetTimeSeconds();
	}
}

void APlayerCar::SlowDown()
{
	if (InSlowingBox)
	{
		ApplySlow = true;
		if (ApplySlow && CarMovementComponent->GetForwardSpeed() * 0.036 > 30.f)
		{
			CarMovementComponent->SetHandbrakeInput(1.0f);
		}
		else
		{
			CarMovementComponent->SetHandbrakeInput(0.0f);
		}
	}
	else
	{
		if (ApplySlow)
		{
			CarMovementComponent->SetHandbrakeInput(0.0f);
			CarMovementComponent->EngineSetup.MaxRPM = 7500.f;
			ApplySlow = false;
		}
	}
}
