// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SkatePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdatedSignature, int32, NewTotalScore, int32, ScoreDelta);

UCLASS()
class SKATEBOARD_API ASkatePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Scoring")
	FOnScoreUpdatedSignature OnScoreUpdated;
	
	UFUNCTION(BlueprintCallable, Category="Scoring")
	void AddScore(int32 Points);

	UFUNCTION(BlueprintPure, Category="Scoring")
	int32 GetCurrentScore() const { return CurrentScore; }

private:
	UPROPERTY()
	int32 CurrentScore = 0;
};
