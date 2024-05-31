// Copyright 2023 Teyon. All Rights Reserved.


#include "Obstacle.h"
#include "Components/BoxComponent.h"


AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ObstacleMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(ObstacleMesh);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));

}

