

#pragma once

#include "CoreMinimal.h"
#include "CarBase.h"
#include "PlayerCar.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APlayerCar : public ACarBase
{
	GENERATED_BODY()
	
public:
	APlayerCar();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	void ResetLap();

	UPROPERTY(BlueprintReadOnly)
	bool InSlowingBox;
	bool ApplySlow;

protected:
	virtual void BeginPlay() override;

	void MoveForward(const FInputActionValue& Value);
	void MoveBackward(const FInputActionValue& Value);
	void Steering(const FInputActionValue& Value);
	void HandBrake(const FInputActionValue& Value);
	void ChangeCamera(const FInputActionValue& Value);

	void RefreshTime();
	void SlowDown();

	int CameraID;

	UPROPERTY(BlueprintReadOnly)
	float BestLapTime;

	UPROPERTY(BlueprintReadOnly)
	float CurrentLapTime;

	UPROPERTY(BlueprintReadOnly)
	TArray<float> LapTimes;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputMappingContext> CarMappingContext;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputAction> MoveBackwardAction;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputAction> SteeringAction;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputAction> HandBrakeAction;

	UPROPERTY(EditAnywhere, Category = Input);
	TObjectPtr<UInputAction> CameraChangeAction;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> Camera1;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> Camera2;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> Camera3;
};
