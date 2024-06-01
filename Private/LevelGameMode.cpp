


#include "LevelGameMode.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PraktykiGameInstance.h"
#include "LevelPraktykiPlayerController.h"
#include "CarBase.h"
#include "PlayerCar.h"
#include "AICarPath.h"
#include "CheckpointTriggerBox.h"


void ALevelGameMode::BeginPlay()
{
	GameWon = false;
	GameLost = false;

	PraktykiGameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());
	if (PraktykiGameInstance)
	{
		PlayerController = Cast<ALevelPraktykiPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			APawn* Pawn = PlayerController->GetPawn();
			if (Pawn)
			{
				PlayersPawn = Cast<APlayerCar>(Pawn);
			}
		}
	}

	TArray<AActor*> PathArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICarPath::StaticClass(), PathArray);
	if (PathArray.Num() > 0)
	{
		ActualPath = Cast<AAICarPath>(PathArray[0]);
	}

	TArray<AActor*> AllTriggerBoxes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpointTriggerBox::StaticClass(), AllTriggerBoxes);
	NumberOfCheckpoints = AllTriggerBoxes.Num();

	if (PraktykiGameInstance->WithBots)
	{
		TArray<AActor*> CarActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarBase::StaticClass(), CarActors);
		for (int i = 0; i < CarActors.Num(); i++)
		{
			ACarBase* Car = Cast<ACarBase>(CarActors[i]);
			if (Car)
			{
				Cars.Add(Car);
			}
		}
		GetWorld()->GetTimerManager().SetTimer(UpdateCarPositionTimerHandle, this, &ALevelGameMode::UpdateCarPositions, 0.5f, true);
	}

	GameWonByBot = false;
}

void ALevelGameMode::Tick(float DeltaTime)
{
	EndGame();
}

void ALevelGameMode::EndGame()
{
	if (!GameWon)
	{
		bool WinCondition = PraktykiGameInstance->GetMapLaps() == PlayersPawn->GetCurrentLap();
		if (WinCondition)
		{
			GameWon = true;
			PlayerController->SetPause(true);
			PlayerController->ShowEndGameWidget();
			PraktykiGameInstance->ResetCurrentGameTime();
			PlayersPawn->ResetLap();
		}
	}

	if (!GameLost)
	{
		bool LostCondition = ((PraktykiGameInstance->GetCurrentMapTime() < 0.0f) || (GameWonByBot));
		if (LostCondition)
		{
			GameLost = true;
			PlayerController->SetPause(true);
			PlayerController->ShowEndGameWidget();
			PraktykiGameInstance->ResetCurrentGameTime();
			PlayersPawn->ResetLap();
		}
	}
}

bool ALevelGameMode::IsPlayerGoingInRightDirection()
{
	USplineComponent* Spline = ActualPath->GetPath();
	FVector PlayerLocation = PlayersPawn->GetActorLocation();
	FVector PlayerForward = PlayersPawn->GetActorForwardVector().GetSafeNormal();

	FVector SplineDirection = Spline->GetTangentAtDistanceAlongSpline
		(Spline->GetDistanceAlongSplineAtLocation(PlayerLocation, ESplineCoordinateSpace::World), ESplineCoordinateSpace::World);

	float DotProduct = FVector::DotProduct(PlayerForward, SplineDirection);

	return DotProduct > 0.0;
}

void ALevelGameMode::SetGameWonByBot()
{
	GameWonByBot = true;
}

void ALevelGameMode::UpdateCarPositions()
{
	Cars.Sort([](const ACarBase& A, const ACarBase& B) {

		if (A.GetCurrentLap() == B.GetCurrentLap())
		{
			if (A.GetCurrentCheckpoint() == B.GetCurrentCheckpoint())
			{
				return A.GetDistanceAlongSpline() > B.GetDistanceAlongSpline();
			}
			else
			{
				return A.GetCurrentCheckpoint() > B.GetCurrentCheckpoint();
			}
		}
		else
		{
			return A.GetCurrentLap() > B.GetCurrentLap();
		}
		
	});

	for (int Index = 0; Index < Cars.Num(); ++Index)
	{
		if (Cars[Index] == PlayersPawn)
		{
			PlayerPosition = Index + 1;
		}
	}
}

int ALevelGameMode::GetMapLaps()
{
	return PraktykiGameInstance->GetMapLaps();
}
