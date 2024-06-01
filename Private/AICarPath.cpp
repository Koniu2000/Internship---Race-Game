


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
