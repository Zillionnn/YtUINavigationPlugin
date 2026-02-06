// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#include "UI/FrameLimitWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void UFrameLimitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FPSArray = {30.0f, 60.0f, 90.0f, 120.0f, 0.0f};

	// PreButton->OnClicked.AddDynamic(this, &UFrameLimitWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UFrameLimitWidget::OnClickNextButton);

	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		CurrentFPS = GSS->GetGameFrameLimit();
		int32 FoundIndex = FPSArray.Find(CurrentFPS);
		if (FoundIndex)
		{
			FPSIndex = FoundIndex;
		}
		SetFPS(CurrentFPS);
	}
}

void UFrameLimitWidget::OnClickPreButton()
{
	if (FPSIndex <= 0)
	{
		FPSIndex = 0;
	}
	else
	{
		FPSIndex--;
	}

	CurrentFPS = FPSArray[FPSIndex];
	SetFPS(CurrentFPS);
}

void UFrameLimitWidget::OnClickNextButton()
{
	int32 LastIndex = FPSArray.Num() - 1;
	if (FPSIndex >= LastIndex)
	{
		FPSIndex = LastIndex;
	}
	else
	{
		FPSIndex++;
	}

	CurrentFPS = FPSArray[FPSIndex];
	SetFPS(CurrentFPS);
}

void UFrameLimitWidget::SetFPS(float InFPS)
{
	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		GSS->SetGameFrameLimit(InFPS);
	}
	if (InFPS == 0.0f)
	{
		FString FPSString = FString::Printf(TEXT("Unlimit"));
		TextBlock_FPS->SetText(FText::FromString(FPSString));
	}
	else
	{
		FString FPSString = FString::Printf(TEXT("%f"), InFPS);
		TextBlock_FPS->SetText(FText::FromString(FPSString));
	}
}
