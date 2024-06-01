


#include "LevelPraktykiPlayerController.h"
#include "Blueprint/UserWidget.h"

void ALevelPraktykiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CountStart();
	CantMove = true;
}

void ALevelPraktykiPlayerController::ShowEndGameWidget()
{
	if (EndGameWidget)
	{
		EndGameWidget->AddToViewport();
	}
}

void ALevelPraktykiPlayerController::CountStart()
{
	if (CountWidget)
	{
		CountWidget->AddToViewport();
		GetWorld()->GetTimerManager().SetTimer(WidgetRemoveTimerHandle, this, &ALevelPraktykiPlayerController::RemoveWidget, 4.0f, false);
	}
}

void ALevelPraktykiPlayerController::RemoveWidget()
{
	if (CountWidget != nullptr)
	{
		CountWidget->RemoveFromParent();
		CantMove = false;
	}
}
