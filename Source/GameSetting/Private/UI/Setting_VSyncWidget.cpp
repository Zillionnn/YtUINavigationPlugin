// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting_VSyncWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void USetting_VSyncWidget::NativeConstruct()
{
	Super::NativeConstruct();


	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		// 自定义图形设置
		GSS->OnCustomSettingChanged.AddUObject(this, &USetting_VSyncWidget::OnSettingChanged);

		// 当改变了整体图形质量
		GSS->OverallScalabilityChanged.AddUObject(this, &USetting_VSyncWidget::OnSettingChanged);
	}


	InitSetting();
}

void USetting_VSyncWidget::CheckChanged(bool bIsChecked)
{
	auto YTGS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGS)
	{
		YTGS->SetVSync(bIsChecked);


		if (bIsChecked)
		{
			FText CStatusText = NSLOCTEXT("i18Namespace", "i_VSyncOn", "ON");
			TextBlock_OnOff->SetText(CStatusText);
		}
		else
		{
			FText CStatusText = NSLOCTEXT("i18Namespace", "i_VSyncOff", "OFF");
			TextBlock_OnOff->SetText(CStatusText);
		}
	}
}

void USetting_VSyncWidget::OnClickPreButton()
{
	CheckChanged(true);
}

void USetting_VSyncWidget::OnClickNextButton()
{
	CheckChanged(false);
}

void USetting_VSyncWidget::InitSetting()
{
	auto YTGS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (YTGS)
	{
		CheckChanged(YTGS->GetVSync());
	}
}

void USetting_VSyncWidget::OnSettingChanged()
{
	InitSetting();
}
