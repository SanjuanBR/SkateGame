// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerState.h"


void ASkatePlayerState::AddScore(int32 Points)
{
	if (Points == 0) return;

	CurrentScore += Points;
	OnScoreUpdated.Broadcast(CurrentScore, Points);
}