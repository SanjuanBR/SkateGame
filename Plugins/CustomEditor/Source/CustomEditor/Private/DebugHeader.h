#pragma once
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

namespace DebugHeader
{
	static void Print(const FString& Message, const FColor& Color = FColor::Cyan)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE,2.f,Color,FString::Printf(TEXT("%s"),*Message));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}

	static void PrintWithKey(const FString& Key, const FString& Value, const FColor& Color = FColor::Cyan)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE,2.f,Color,FString::Printf(TEXT("%s: %s"),*Key, *Value));
			UE_LOG(LogTemp, Warning, TEXT("%s: %s"),*Key, *Value);
		}
	}

	static EAppReturnType::Type ShowMessageDialog(EAppMsgType::Type MessageType,const FString& Message, bool bShowMessageWarning = false)
	{
		if(bShowMessageWarning)
		{
			const FText Title = FText::FromString(TEXT("Warning"));
			return FMessageDialog::Open(MessageType,FText::FromString(Message), Title);
		}
	
		return FMessageDialog::Open(MessageType,FText::FromString(Message));
	}

	static void ShowNotifyInfo(const FString& Message)
	{
		FNotificationInfo NotifyInfo(FText::FromString(Message));
		NotifyInfo.bUseLargeFont = true;
		NotifyInfo.FadeOutDuration = 7.f;

		FSlateNotificationManager::Get().AddNotification(NotifyInfo);
	}
}