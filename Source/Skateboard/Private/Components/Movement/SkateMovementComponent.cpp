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

	if (!PawnOwner || !UpdatedComponent || IsFalling()){return;}

	const FVector SkateAcceleration = PawnOwner->GetActorForwardVector() * AccelerationForce * ForwardInputScale;

	const FVector CurrentVelocity = Velocity;
	const float DecelerationRate = bIsBraking ? BrakingForce : SkateGroundFriction;
	const FVector Deceleration = -CurrentVelocity.GetSafeNormal() * DecelerationRate;
	
	if (ForwardInputScale <= KINDA_SMALL_NUMBER)
	{
		Velocity += Deceleration * DeltaTime;
	}
	else
	{
		Velocity += SkateAcceleration * DeltaTime;
	}

	if (Velocity.SizeSquared() > FMath::Square(MaxSkateSpeed))
	{
		Velocity = Velocity.GetSafeNormal() * MaxSkateSpeed;
	}
	
	if (FVector::DotProduct(Velocity, CurrentVelocity) < 0.f)
	{
		Velocity = FVector::ZeroVector;
	}
	
	ForwardInputScale = 0.0f;
}
