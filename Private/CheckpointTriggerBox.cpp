// Copyright 2023 Teyon. All Rights Reserved.


#include "CheckpointTriggerBox.h"
#include "Components/BoxComponent.h"

ACheckpointTriggerBox::ACheckpointTriggerBox()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(1000.f, 50.f, 1000.f));
}

