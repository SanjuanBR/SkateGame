#include "Components/Movement/SkateMovementComponent.h"
#include "DrawDebugHelpers.h"

USkateMovementComponent::USkateMovementComponent()
{
	MaxWalkSpeed = MaxSkateSpeed;
	bOrientRotationToMovement = true;
	RotationRate = FRotator(0.0f, 200.0f, 0.0f);
}

