// Copyright 2023 Teyon. All Rights Reserved.


#include "FrontChaosVehicleWheel.h"

UFrontChaosVehicleWheel::UFrontChaosVehicleWheel()
{
	AxleType = EAxleType::Front;
	WheelRadius = 35.f;
	WheelWidth = 20.f;
	CorneringStiffness = 500.f;
	FrictionForceMultiplier = 4.f;
	bAffectedByEngine = true;
	bAffectedBySteering = true;
}
