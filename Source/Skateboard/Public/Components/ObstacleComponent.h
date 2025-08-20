// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ObstacleComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SKATEBOARD_API UObstacleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObstacleComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FGameplayTag ObstacleTag;
	
};
