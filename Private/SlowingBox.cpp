// Copyright 2023 Teyon. All Rights Reserved.

#include "SlowingBox.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"

ASlowingBox::ASlowingBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SlowingBox"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoxExtent(FVector(80.f, 90.f, 10.f));
}

void ASlowingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlowingBox::BeginPlay()
{
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlowingBox::OnBoxOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASlowingBox::OnBoxEndOverlap);
}

void ASlowingBox::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if(Player)
	{
		Player->InSlowingBox = true;
	}
}

void ASlowingBox::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		Player->InSlowingBox = false;
	}
}

