// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ResolutionScaleWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Engine/Engine.h"
#include "YtUIGameInstance.h"


void UResolutionScaleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ScreenPercentage = 100.f;
	MaxScreenPercentage = 100.0f;
	MinScreenPercentage = 1.0f;

	GetScreenPercentage();
}


void UResolutionScaleWidget::Decrease(float Value)
{
	ScreenPercentage -= Value;
	if (ScreenPercentage <= MinScreenPercentage)
	{
		ScreenPercentage = MinScreenPercentage;
	}
	SetScreenPercentage();
}

void UResolutionScaleWidget::Increase(float Value)
{
	ScreenPercentage += Value;
	if (ScreenPercentage >= MaxScreenPercentage)
	{
		ScreenPercentage = MaxScreenPercentage;
	}
	SetScreenPercentage();
}

void UResolutionScaleWidget::SetScreenPercentage()
{
	auto YGS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YGS)
	{
		YGS->SetResolutionScale(ScreenPercentage);

		FString ScaleString = FString::Printf(TEXT("%d"), static_cast<int>(ScreenPercentage));
		Text_ResolutionScaleValue->SetText(FText::FromString(ScaleString));
	}
}

float UResolutionScaleWidget::GetScreenPercentage()
{
	auto YGS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YGS)
	{
		ScreenPercentage = YGS->GetResolutionScale();
		SetScreenPercentage();
	}
	return ScreenPercentage;
}
