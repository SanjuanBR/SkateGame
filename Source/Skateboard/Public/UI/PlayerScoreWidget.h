// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class SKATEBOARD_API UPlayerScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UFUNCTION()
	void HandleScoreUpdated(int32 NewTotalScore, int32 ScoreDelta);
};
