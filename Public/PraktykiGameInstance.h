

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PraktykiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UPraktykiGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPraktykiGameInstance();
	void ResetCurrentGameTime();

	UPROPERTY(BlueprintReadWrite)
	float GameTime;

	UPROPERTY(BlueprintReadWrite)
	float CurrentGameTime;

	UPROPERTY(BlueprintReadWrite)
	int Laps;

	UPROPERTY(BlueprintReadWrite)
	bool WithBots;

	UFUNCTION(BlueprintCallable)
	void AddOneGameTime();

	UFUNCTION(BlueprintCallable)
	void AddFiveGameTime();

	UFUNCTION(BlueprintCallable)
	void SubOneGameTime();

	UFUNCTION(BlueprintCallable)
	void SubFiveGameTime();

	UFUNCTION(BlueprintCallable)
	void AddOneGameLap();

	UFUNCTION(BlueprintCallable)
	void AddFiveGameLaps();

	UFUNCTION(BlueprintCallable)
	void SubOneGameLap();

	UFUNCTION(BlueprintCallable)
	void SubFiveGameLaps();

	FORCEINLINE float GetMapTime() const { return GameTime; }
	FORCEINLINE int GetMapLaps() const { return Laps; }
	FORCEINLINE float GetCurrentMapTime() const { return CurrentGameTime; }
};
