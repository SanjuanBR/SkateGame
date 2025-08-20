// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SkateCharacter.generated.h"

class UScoreDataAsset;
class USkateMovementComponent;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SKATEBOARD_API ASkateCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkateCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Input" , meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* SkaterMappingContext;

	UPROPERTY(EditAnywhere, Category = "Setup|Input" , meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input" , meta = (AllowPrivateAccess = "true"))
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input" , meta = (AllowPrivateAccess = "true"))
	UInputAction* BrakeAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input", meta = (AllowPrivateAccess = "true"))
	FVector JumpDetectionBoxHalfSize = FVector(30.f, 30.f, 60.f);

	UPROPERTY()
	USkateMovementComponent* SkaterMovementComponent;

	UPROPERTY()
	TSet<AActor*> ScoredObstaclesInCombo;

	UPROPERTY(EditAnywhere, Category = "Setup|Scoring")
	UScoreDataAsset* ScoreData;

	float JumpChargeStartTime;
	FVector JumpStartLocation;
	
	void MoveForward(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void StartBraking(const FInputActionValue& Value);
	void StopBraking(const FInputActionValue& Value);
	void StartJumpCharge(const FInputActionValue& Value);
	void ReleaseJump(const FInputActionValue& Value);

	void ScoreJump();
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	
	
};