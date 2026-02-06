// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#include "UI/WindowModeWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void UWindowModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// PreButton->OnClicked.AddDynamic(this, &UWindowModeWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UWindowModeWidget::OnClickNextButton);

	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		ModeIndex = YTGSS->GetWindowMode();
		SetWindowMode();
	}
}

void UWindowModeWidget::OnClickPreButton()
{
	ModeIndex--;

	if (ModeIndex <= 0)
	{
		ModeIndex = 0;
	}

	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		YTGSS->SetWindowMode(static_cast<EWindowMode::Type>(ModeIndex));
	}

	SetWindowMode();
}

void UWindowModeWidget::OnClickNextButton()
{
	ModeIndex++;
	if (ModeIndex >= 2)
	{
		ModeIndex = 2;
	}

	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		YTGSS->SetWindowMode(static_cast<EWindowMode::Type>(ModeIndex));
	}

	SetWindowMode();
}

void UWindowModeWidget::SetWindowMode()
{
	FString ModeString;
	if (ModeIndex == 0)
	{
		ModeString = "Fullscreen";
	}
	else if (ModeIndex == 1)
	{
		ModeString = "WindowedFullscreen";
	}
	else if (ModeIndex == 2)
	{
		ModeString = "Windowed";
	}

	TextBlock_WindowMode->SetText(FText::FromString(ModeString));
}
