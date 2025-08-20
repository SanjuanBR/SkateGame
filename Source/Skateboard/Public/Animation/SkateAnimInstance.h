// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkateAnimInstance.generated.h"

class USkateMovementComponent;
class ASkateCharacter;

UCLASS()
class SKATEBOARD_API USkateAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsPushing;

private:
	UPROPERTY()
	ASkateCharacter* SkateCharacter;

	UPROPERTY()
	USkateMovementComponent* SkateMovementComponent;
};
