#include "Components/Movement/SkateMovementComponent.h"

USkateMovementComponent::USkateMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GroundFriction = 0.0f;
	BrakingDecelerationWalking = 0.0f;
	BrakingFriction = 0.0f;

	RotationRate = SkateRotationRate.Rotation();

	bOrientRotationToMovement = false;
	bUseControllerDesiredRotation = true;

	bIsBraking = false;
	CurrentSpeed = 0.0f;
	ForwardInputScale = 0.0f;
}

void USkateMovementComponent::AddSkateInput(float Scale)
{
	ForwardInputScale = Scale;
}

void USkateMovementComponent::SetBraking(bool bNewBrakingState)
{
	bIsBraking = bNewBrakingState;
}

void USkateMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent) return;

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
	
	if (CurrentSpeed > 0.f)
	{
		FVector Delta = Velocity * DeltaTime;
		FHitResult Hit;
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
		}
	}
	
	ForwardInputScale = 0.0f;
}
