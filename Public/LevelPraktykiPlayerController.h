

#pragma once

#include "CoreMinimal.h"
#include "PraktykiPlayerController.h"
#include "LevelPraktykiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ALevelPraktykiPlayerController : public APraktykiPlayerController
{
	GENERATED_BODY()
	
public:
	void ShowEndGameWidget();
	void CountStart();

	FORCEINLINE bool GetCantMove() const { return CantMove; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> CountWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> EndGameWidget;

private:
	void RemoveWidget();

	bool CantMove;
	FTimerHandle WidgetRemoveTimerHandle;
};
