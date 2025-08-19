// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkateMovementDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SKATEBOARD_API USkateMovementDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MaxSpeed = 1200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float Acceleration = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float Deceleration = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float GroundFriction = 0.98f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float AirFriction = 0.995f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotation")
	float RotationSpeed = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotation")
	float AirRotationSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump")
	float JumpImpulse = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump")
	float JumpCutMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Push")
	float PushForce = 600.0f;
};