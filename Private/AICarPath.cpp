// Copyright 2023 Teyon. All Rights Reserved.


#include "AICarPath.h"
#include "Components/SplineComponent.h"

AAICarPath::AAICarPath()
{
	PrimaryActorTick.bCanEverTick = true;

	Path = CreateDefaultSubobject<USplineComponent>(TEXT("Path"));
	Path->SetClosedLoop(true);
}

USplineComponent* AAICarPath::GetPath() const
{
	return Path;
}
