
#include "PraktykiGameInstance.h"

void UPraktykiGameInstance::ResetCurrentGameTime()
{
	CurrentGameTime = GameTime;
}

UPraktykiGameInstance::UPraktykiGameInstance()
{
	GameTime = 120.f;
	Laps = 2;
	ResetCurrentGameTime();
	WithBots = false;
}

void UPraktykiGameInstance::AddOneGameTime()
{
	GameTime++;
	ResetCurrentGameTime();
}

void UPraktykiGameInstance::AddFiveGameTime()
{
	GameTime += 5.f;
	ResetCurrentGameTime();
}

void UPraktykiGameInstance::SubOneGameTime()
{
	GameTime--;
	ResetCurrentGameTime();
}

void UPraktykiGameInstance::SubFiveGameTime()
{
	GameTime -= 5.f;
	ResetCurrentGameTime();
}

void UPraktykiGameInstance::AddOneGameLap()
{
	Laps++;
}

void UPraktykiGameInstance::AddFiveGameLaps()
{
	Laps += 5;
}

void UPraktykiGameInstance::SubOneGameLap()
{
	Laps--;
}

void UPraktykiGameInstance::SubFiveGameLaps()
{
	Laps -= 5;
}
