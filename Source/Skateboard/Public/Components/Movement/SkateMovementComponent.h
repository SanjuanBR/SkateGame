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

	// Atualiza a cada frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Input externo (Character chama isso)
	void AddSkateInput( float Scale);

	// Nova função para controlar o estado de frenagem
	void SetBraking(bool bNewBrakingState);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	FVector SkateRotationRate = FVector(0,200,0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationForce = 6000.0f;   // acelera forte, ganha velocidade rápido

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float TurnStrength = 50.0f;         // sensibilidade de curva (pode ir até 300 pra arcade)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float BrakingForce = 8000.0f;        // freia bem mais forte que acelera

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float MaxSkateSpeed = 6000.0f;       // velocidade máxima (bem rápida)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float AccelerationSmoothness = 6.0f; // quanto mais alto, mais rápido responde ao input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float DecelerationSmoothness = 70.f; // soltar input leva um tempinho pra parar

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(AllowPrivateAccess=true))
	float SkateGroundFriction = 200.f;
	
	bool bIsBraking;

	float CurrentSpeed;
	float ForwardInputScale;
	
};
