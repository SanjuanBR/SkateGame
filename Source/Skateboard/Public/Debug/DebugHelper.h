#pragma once

#include "Kismet/KismetSystemLibrary.h"

namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1, ELogVerbosity::Type LogVerbosity = ELogVerbosity::Warning)
	{
		if (GEngine)
		{
			const FString MsgToScreen = FString::Printf(TEXT("\n\n                    %s"),*Msg);
			GEngine->AddOnScreenDebugMessage(InKey,7.f,Color,MsgToScreen);

			UE_LOG(LogTemp,Warning,TEXT("%s"),*Msg);
		}
	}

	static void PrintError(const FString& Msg, const FColor& Color = FColor::Red, int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString MsgToScreen = FString::Printf(TEXT("\n\n                    %s"),*Msg);
			GEngine->AddOnScreenDebugMessage(InKey,7.f,Color,MsgToScreen);

			UE_LOG(LogTemp,Error,TEXT("ERROR: %s"),*Msg);
		}
	}

	static void DrawTransformDirections(const UObject* WorldContextObject, const FTransform& Transform)
	{
		UKismetSystemLibrary::DrawDebugArrow(WorldContextObject, Transform.GetLocation(), Transform.GetLocation() + Transform.GetRotation().GetForwardVector() * 10.f, 5.f,FColor::Red, 10.f);
		UKismetSystemLibrary::DrawDebugArrow(WorldContextObject, Transform.GetLocation(), Transform.GetLocation() + Transform.GetRotation().GetRightVector() * 10.f, 5.f,FColor::Green, 10.f);
		UKismetSystemLibrary::DrawDebugArrow(WorldContextObject, Transform.GetLocation(), Transform.GetLocation() + Transform.GetRotation().GetUpVector() * 10.f, 5.f,FColor::Blue, 10.f);
	}
}
