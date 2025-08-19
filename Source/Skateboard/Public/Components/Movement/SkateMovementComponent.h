#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkateMovementComponent.generated.h"

UCLASS()
class SKATEBOARD_API USkateMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	USkateMovementComponent();

	float GetAccelerationForce() const {return AccelerationForce;}
	float GetTurnStrength() const {return TurnStrength;}
	float GetBrakingForce() const {return BrakingForce;}

private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationForce = 1000.0f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float TurnStrength = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float BrakingForce = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float MaxSkateSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationSmoothness = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float DecelerationSmoothness = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float SkateGroundFriction = 0.1f;

	float CurrentAcceleration;
	FVector SmoothedInputVector;
	
	
};
