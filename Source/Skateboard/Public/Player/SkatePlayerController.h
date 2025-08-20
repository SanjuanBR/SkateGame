// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkatePlayerController.generated.h"


class UPlayerScoreWidget;

UCLASS()
class SKATEBOARD_API ASkatePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UPlayerScoreWidget> PlayerScoreWidgetClass;

	UPROPERTY()
	UPlayerScoreWidget* PlayerScoreWidgetInstance;
};
