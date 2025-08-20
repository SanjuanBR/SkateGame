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
	
	UFUNCTION(BlueprintPure, Category="Movement")
	float GetForwardInputScale() const { return ForwardInputScale; }
	
	void DoChargedJump(float ChargeDuration);
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddSkateInput( float Scale);
	
	void SetBraking(bool bNewBrakingState);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	FVector SkateRotationRate = FVector(0,200,0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationForce = 6000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float TurnStrength = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float BrakingForce = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float MaxSkateSpeed = 6000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationSmoothness = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float DecelerationSmoothness = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float SkateGroundFriction = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Jump", meta=(AllowPrivateAccess=true))
	float MinJumpForce = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Jump", meta=(AllowPrivateAccess=true))
	float MaxJumpForce = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Jump", meta=(AllowPrivateAccess=true))
	float MaxJumpChargeTime = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup|Jump", meta=(AllowPrivateAccess=true))
	float SkateJumpZVelocity = 700.f;
	
	bool bIsBraking;
	
	float ForwardInputScale;
	
};
