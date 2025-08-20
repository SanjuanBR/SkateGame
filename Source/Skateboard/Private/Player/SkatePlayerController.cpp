// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SkatePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlayerScoreWidget.h"

void ASkatePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (PlayerScoreWidgetClass)
		{
			PlayerScoreWidgetInstance = CreateWidget<UPlayerScoreWidget>(this, PlayerScoreWidgetClass);
			
			if (PlayerScoreWidgetInstance)
			{
				PlayerScoreWidgetInstance->AddToViewport();
			}
		}
	}
}
