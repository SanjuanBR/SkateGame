#include "Components/Movement/SkateMovementComponent.h"

#include "GameFramework/Character.h"

USkateMovementComponent::USkateMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GroundFriction = 0.0f;
	BrakingDecelerationWalking = 0.0f;
	BrakingFriction = 0.0f;

	RotationRate = SkateRotationRate.Rotation();

	bOrientRotationToMovement = false;
	bUseControllerDesiredRotation = true;

	AirControl = 0.2f;

	GravityScale = 2.5f;

	bIsBraking = false;
	ForwardInputScale = 0.0f;
}

void USkateMovementComponent::AddSkateInput(float Scale)
{
	ForwardInputScale = FMath::Clamp(Scale, -1.0f, 1.0f);
}

void USkateMovementComponent::SetBraking(bool bNewBrakingState)
{
	bIsBraking = bNewBrakingState;
}

void USkateMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USkateMovementComponent::DoChargedJump(float ChargeDuration)
{
	const float ChargeRatio = FMath::Clamp(ChargeDuration / MaxJumpChargeTime, 0.0f, 1.0f);
	const float LaunchForce = FMath::Lerp(MinJumpForce, MaxJumpForce, ChargeRatio);
	const FVector LaunchVelocityImpulse = FVector(0.0f, 0.0f, LaunchForce);
        
	CharacterOwner->LaunchCharacter(LaunchVelocityImpulse, false, true);
}

void USkateMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent) { return; }

	if (IsFalling())
	{
		return;
	}

	float CurrentSpeed = Velocity.Size();

	if (ForwardInputScale > KINDA_SMALL_NUMBER)
	{
		CurrentSpeed += AccelerationForce * ForwardInputScale * DeltaTime;
	}
	else
	{
		const float DecelerationRate = bIsBraking ? BrakingForce : SkateGroundFriction;
		CurrentSpeed -= DecelerationRate * DeltaTime;
	}

	CurrentSpeed = FMath::Clamp(CurrentSpeed, 0.0f, MaxSkateSpeed);

	Velocity = PawnOwner->GetActorForwardVector() * CurrentSpeed;

	ForwardInputScale = 0.0f;
}
