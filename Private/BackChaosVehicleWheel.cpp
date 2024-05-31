// Copyright 2023 Teyon. All Rights Reserved.


#include "BackChaosVehicleWheel.h"

UBackChaosVehicleWheel::UBackChaosVehicleWheel()
{
	AxleType = EAxleType::Rear;
	WheelRadius = 35.f;
	WheelWidth = 20.f;
	CorneringStiffness = 500.f;
	FrictionForceMultiplier = 4.f;
	bAffectedBySteering = false;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
}
