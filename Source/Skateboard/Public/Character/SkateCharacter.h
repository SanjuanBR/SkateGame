// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SkateCharacter.generated.h"

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
	
	UPROPERTY(EditAnywhere, Category = "Setup|Input")
	UInputMappingContext* SkaterMappingContext;

	UPROPERTY(EditAnywhere, Category = "Setup|Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input")
	UInputAction* BrakeAction;

	UPROPERTY(EditAnywhere, Category = "Setup|Input")
	UInputAction* JumpAction;
	
	USkateMovementComponent* SkaterMovementComponent;

	float JumpChargeStartTime;
	
	void MoveForward(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void StartBraking(const FInputActionValue& Value);
	void StopBraking(const FInputActionValue& Value);
	void StartJumpCharge(const FInputActionValue& Value);
	void ReleaseJump(const FInputActionValue& Value);
};