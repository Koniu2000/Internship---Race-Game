


#include "PraktykiPlayerController.h"
#include "Blueprint/UserWidget.h"

void APraktykiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (Widget)
	{
		Widget->AddToViewport();
	}
}
