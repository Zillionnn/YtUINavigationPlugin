// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting_AntiAliasingMethodWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void USetting_AntiAliasingMethodWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MethodArray = {0, 1, 2, 3, 4};

	// PreButton->OnClicked.AddDynamic(this, &UFrameLimitWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &UFrameLimitWidget::OnClickNextButton);
}

/**
 * 蓝图中调用
 * @param InMethod 
 */
void USetting_AntiAliasingMethodWidget::InitMethod(int32 InMethod)
{
	MethodArray = {0, 1, 2, 3, 4};

	UE_LOG(LogTemp, Log, TEXT("MethodArray.Num() = %d"), MethodArray.Num());

	CurrentMethod = InMethod;
	int32 FoundIndex = MethodArray.Find(CurrentMethod);
	if (FoundIndex != INDEX_NONE)
	{
		MethodIndex = FoundIndex;
	}
}


void USetting_AntiAliasingMethodWidget::OnClickPreButton()
{
	if (MethodIndex <= 0)
	{
		MethodIndex = 0;
	}
	else
	{
		MethodIndex--;
	}

	CurrentMethod = MethodArray[MethodIndex];
	SetAntialiasingMethod(CurrentMethod);
}

void USetting_AntiAliasingMethodWidget::OnClickNextButton()
{
	int32 MaxMethodIndex = MethodArray.Num() - 1;
	if (MethodIndex >= MaxMethodIndex)
	{
		MethodIndex = MaxMethodIndex;
	}
	else
	{
		MethodIndex++;
	}

	CurrentMethod = MethodArray[MethodIndex];
	SetAntialiasingMethod(CurrentMethod);
}


void USetting_AntiAliasingMethodWidget::SetAntialiasingMethod_Implementation(int32 InMethod)
{
	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		GSS->SetAntiAliasingMethod(InMethod);
	}

	FString MethodString;
	switch (InMethod)
	{
	case 0:
		{
			MethodString = TEXT("None");
			break;
		}
	case 1:
		{
			MethodString = TEXT("FXAA");
			break;
		}
	case 2:
		{
			MethodString = TEXT("TAA");
			break;
		}
	case 3:
		{
			MethodString = TEXT("MSAA");
			break;
		}
	case 4:
		{
			MethodString = TEXT("TSR");

			break;
		}
	default: break;
	}
	TextBlock_AntiMethod->SetText(FText::FromString(MethodString));
}
