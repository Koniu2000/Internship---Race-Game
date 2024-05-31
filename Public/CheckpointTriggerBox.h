// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckpointTriggerBox.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ACheckpointTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ACheckpointTriggerBox();
	FORCEINLINE int GetCheckpointID() const { return CheckpointID; }

protected:
	UPROPERTY(EditAnywhere)
	int CheckpointID;

private:
	TObjectPtr<UBoxComponent> TriggerBox;
};
