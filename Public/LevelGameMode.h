// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Praktyki/PraktykiGameModeBase.h"
#include "LevelGameMode.generated.h"

class UPraktykiGameInstance;
class APlayerCar;
class ALevelPraktykiPlayerController;
class AAICarPath;
class ACarBase;

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ALevelGameMode : public APraktykiGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	int GetMapLaps();
	void SetGameWonByBot();
	void UpdateCarPositions();

	UFUNCTION(BlueprintCallable)
	bool IsPlayerGoingInRightDirection();

	FORCEINLINE int GetNumOfCheckPoints() const { return NumberOfCheckpoints; }

protected:
	virtual void BeginPlay() override;
	void EndGame();

	int NumberOfCheckpoints;

	bool GameWonByBot;

	UPROPERTY(BlueprintReadOnly)
	bool GameWon;

	UPROPERTY(BlueprintReadOnly)
	bool GameLost;

	UPROPERTY(BlueprintReadOnly)
	int PlayerPosition;

	TArray<ACarBase*> Cars;

	TObjectPtr<UPraktykiGameInstance> PraktykiGameInstance;
	TObjectPtr<APlayerCar> PlayersPawn;
	TObjectPtr<ALevelPraktykiPlayerController> PlayerController;

	FTimerHandle UpdateCarPositionTimerHandle;
	FTimerHandle UpdateWinConditionHandle;

private:
	TObjectPtr<AAICarPath> ActualPath;
};
