// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/SkateCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/ObstacleComponent.h"
#include "Components/Movement/SkateMovementComponent.h"
#include "Data/ScoreDataAsset.h"
#include "Debug/DebugHelper.h"
#include "Kismet/KismetSystemLibrary.h"


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
        
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASkateCharacter::StartJumpCharge);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASkateCharacter::ReleaseJump);
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

void ASkateCharacter::StartJumpCharge(const FInputActionValue& Value)
{
    JumpChargeStartTime = GetWorld()->GetTimeSeconds();

    JumpStartLocation = GetActorLocation();
}

void ASkateCharacter::ReleaseJump(const FInputActionValue& Value)
{
    if (SkaterMovementComponent)
    {
        const float ChargeDuration = GetWorld()->GetTimeSeconds() - JumpChargeStartTime;
        SkaterMovementComponent->DoChargedJump(ChargeDuration);
    }
}

void ASkateCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
    Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

    // UEnum* EnumRef = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMovementMode"), true);
    // FString StringStatus = EnumRef->GetNameStringByValue((int64)PrevMovementMode);
    //
    // Debug::Print("PrevMovementMode: " + StringStatus);
    
    if (PrevMovementMode == MOVE_Falling && GetCharacterMovement()->IsMovingOnGround())
    {
        ScoreJump();
        ScoredObstaclesInCombo.Empty();
    }
}

void ASkateCharacter::ScoreJump()
{
    if (!ScoreData)
    {
        UE_LOG(LogTemp, Warning, TEXT("ScoreData asset não foi definido no SkateCharacter."));
        return;
    }

    const FVector JumpEndLocation = GetActorLocation();
    const FRotator Orientation = GetActorRotation();
    
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
    
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    TArray<FHitResult> HitResults;

    // Executa o Box Trace do início ao fim do pulo
    UKismetSystemLibrary::BoxTraceMultiForObjects(
        GetWorld(),
        JumpStartLocation,
        JumpEndLocation,
        JumpDetectionBoxHalfSize,
        Orientation,
        ObjectTypes,
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true
    );

    int32 TotalScoreForThisJump = 0;

    for (const FHitResult& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && !ScoredObstaclesInCombo.Contains(HitActor))
        {
            UObstacleComponent* ObstacleComp = HitActor->FindComponentByClass<UObstacleComponent>();
            if (ObstacleComp)
            {
                if (const int32* ScorePtr = ScoreData->ScoreMap.Find(ObstacleComp->ObstacleTag))
                {
                    TotalScoreForThisJump += *ScorePtr;
                    ScoredObstaclesInCombo.Add(HitActor);
                }
            }
        }
    }

    if (TotalScoreForThisJump > 0)
    {
        Debug::Print("PONTUAÇÃO TOTAL DO PULO: " + FString::FromInt(TotalScoreForThisJump));
    }
}