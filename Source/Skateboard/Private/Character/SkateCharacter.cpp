// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/SkateCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/Movement/SkateMovementComponent.h"


ASkateCharacter::ASkateCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USkateMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bUsePawnControlRotation = true; // Rotaciona o braço baseado na rotação do controlador
    CameraBoom->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f)); // Inclinação inicial
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Anexa a câmera ao final do SpringArm
    FollowCamera->bUsePawnControlRotation = false; // A câmera não rotaciona sozinha
    
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 5.0f;

    SkaterMovementComponent = Cast<USkateMovementComponent>(GetCharacterMovement());
    ensureMsgf(SkaterMovementComponent, TEXT("Failed to get SkaterMovement for %s. Check default subobject class."), *GetName());
}

void ASkateCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (SkaterMappingContext)
            {
                Subsystem->AddMappingContext(SkaterMappingContext, 0);
            }
        }
    }
}

void ASkateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASkateCharacter::MoveForward);
        EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASkateCharacter::Turn);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &ASkateCharacter::StartBraking);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ASkateCharacter::StopBraking);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASkateCharacter::RequestJump);
    }
}

void ASkateCharacter::MoveForward(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    if (Controller != nullptr && AxisValue != 0.0f)
    {
        if (SkaterMovementComponent)
        {
            SkaterMovementComponent->AddSkateInput(AxisValue);
        }
    }
}

void ASkateCharacter::Turn(const FInputActionValue& Value)
{
    const float AxisValue = Value.Get<float>();
    if (Controller != nullptr && AxisValue != 0.0f)
    {
        if (SkaterMovementComponent)
        {
            AddControllerYawInput(AxisValue * SkaterMovementComponent->GetTurnStrength() * GetWorld()->GetDeltaSeconds());
        }
    }
}

void ASkateCharacter::StartBraking(const FInputActionValue& Value)
{
    if (SkaterMovementComponent)
    {
        SkaterMovementComponent->SetBraking(true);
    }
}

void ASkateCharacter::StopBraking(const FInputActionValue& Value)
{
    if (SkaterMovementComponent)
    {
        SkaterMovementComponent->SetBraking(false);
    }
}

void ASkateCharacter::RequestJump(const FInputActionValue& Value)
{
    Jump();
}