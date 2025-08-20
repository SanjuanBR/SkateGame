// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ScoreDataAsset.generated.h"

UCLASS()
class SKATEBOARD_API UScoreDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scoring")
	TMap<FGameplayTag, int32> ScoreMap;
};
