// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerScoreWidget.h"

#include "Components/TextBlock.h"
#include "Debug/DebugHelper.h"
#include "Player/SkatePlayerState.h"

void UPlayerScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!IsDesignTime())
	{
		ASkatePlayerState* SkatePS = GetOwningPlayerState<ASkatePlayerState>();
		if (SkatePS)
		{
			SkatePS->OnScoreUpdated.AddDynamic(this, &UPlayerScoreWidget::HandleScoreUpdated);
			HandleScoreUpdated(SkatePS->GetCurrentScore(), 0);
		}
	}
}

void UPlayerScoreWidget::HandleScoreUpdated(int32 NewTotalScore, int32 ScoreDelta)
{
	Debug::Print("NewTotalScore: " + NewTotalScore);
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(NewTotalScore));
	}
}