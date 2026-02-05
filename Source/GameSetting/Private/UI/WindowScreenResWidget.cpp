// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WindowScreenResWidget.h"

#include "YtGameSettingSubsystem.h"
#include "GenericPlatform/GenericApplication.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void UWindowScreenResWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// PreButton->OnClicked.AddDynamic(this, &UWindowScreenResWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UWindowScreenResWidget::OnClickNextButton);

	ResolutionList = {FIntPoint(800, 600), FIntPoint(1280, 720), FIntPoint(1920, 1080)};
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);
	FIntPoint MaxResolution = FIntPoint(DisplayMetrics.PrimaryDisplayWorkAreaRect.Right, DisplayMetrics.PrimaryDisplayWorkAreaRect.Bottom);

	UE_LOG(LogTemp, Log, TEXT("screen max resolution >>> %s"), *MaxResolution.ToString());

	if (MaxResolution.X == 2560)
	{
		ResolutionList.Add(MaxResolution);
	}
	if (MaxResolution.X > 2560)
	{
		ResolutionList.Add(FIntPoint(2560, 1440));
		ResolutionList.Add(MaxResolution);
	}


	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		ScreenRes = YTGSS->GetScreenResolution();
		SetResolution(ScreenRes);
	}
}

void UWindowScreenResWidget::OnClickPreButton()
{
	if (ModeIndex <= 0)
	{
		ModeIndex = 0;
	}
	else
	{
		ModeIndex--;
	}
	FIntPoint Res = ResolutionList[ModeIndex];

	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		YTGSS->SetScreenResolution(Res);
	}

	SetResolution(Res);
}

void UWindowScreenResWidget::OnClickNextButton()
{
	int32 LastIndex = ResolutionList.Num() - 1;
	if (ModeIndex >= LastIndex)
	{
		ModeIndex = LastIndex;
	}
	else
	{
		ModeIndex++;
	}

	FIntPoint Res = ResolutionList[ModeIndex];
	auto YTGSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGSS)
	{
		YTGSS->SetScreenResolution(Res);
	}

	SetResolution(Res);
}

void UWindowScreenResWidget::SetResolution(FIntPoint InPoint)
{
	FString ResString = FString::Printf(TEXT("%d x %d"), InPoint.X, InPoint.Y);
	TextBlock_ScreenRes->SetText(FText::FromString(ResString));
}
