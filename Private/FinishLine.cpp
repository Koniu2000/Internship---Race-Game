// Copyright 2023 Teyon. All Rights Reserved.


#include "FinishLine.h"
#include "Components/BoxComponent.h"

AFinishLine::AFinishLine()
{
	SecondBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondBoxComponent"));
	SecondBoxComponent->SetupAttachment(ObstacleMesh);

	MetalTabMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MetalTabMesh"));
	MetalTabMesh->SetupAttachment(ObstacleMesh);

	MetalTabBottomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MetalTabBottomMesh"));
	MetalTabBottomMesh->SetupAttachment(ObstacleMesh);

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->SetupAttachment(ObstacleMesh);

	FinishLineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FinishLineMesh"));
	FinishLineMesh->SetupAttachment(ObstacleMesh);
}
