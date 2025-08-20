#include "Animation/SkateAnimInstance.h" 
#include "Character/SkateCharacter.h"
#include "Components/Movement/SkateMovementComponent.h"


void USkateAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SkateCharacter = Cast<ASkateCharacter>(TryGetPawnOwner());
	if (SkateCharacter)
	{
		SkateMovementComponent = SkateCharacter->FindComponentByClass<USkateMovementComponent>();
	}
}

void USkateAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!SkateCharacter || !SkateMovementComponent)
	{
		return;
	}

	GroundSpeed = SkateCharacter->GetVelocity().Size2D();
	bIsFalling = SkateMovementComponent->IsFalling();
	bIsPushing = SkateCharacter->IsPushingInput();
}