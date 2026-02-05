// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingItemWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "YtUIGameInstance.h"


void USettingItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_QualityName->SetText(QualityNameToString(SettingType));
}

void USettingItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


	if (SettingType == EGameSettingsQuality::OverallScalabilityLevel)
	{
		// 自定义图形设置
		auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
		if (GSS)
		{
			UE_LOG(LogTemp, Log, TEXT("sETTING item widget native construct BIND"));
			GSS->OnCustomSettingChanged.AddUObject(this, &USettingItemWidget::OnCustomSettingChanged);
		}
	}
	else
	{
		// 当改变了整体图形质量
		auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
		if (GSS)
		{
			UE_LOG(LogTemp, Log, TEXT("sETTING item widget native construct BIND"));
			GSS->OverallScalabilityChanged.AddUObject(this, &USettingItemWidget::OnOverallScalabilityChanged);
		}
	}


	// PreButton->OnClicked.AddDynamic(this, &USettingItemWidget::OnClickPreButton);
	// NextButton->OnClicked.AddDynamic(this, &USettingItemWidget::OnClickNextButton);

	InitSettingType(SettingType);
}

void USettingItemWidget::NativeDestruct()
{
	UE_LOG(LogTemp, Log, TEXT("sETTING item widget NativeDestruct"));

	Super::NativeDestruct();
}

void USettingItemWidget::OnClickPreButton()
{
	if (CurrentQuality <= 0)
	{
		CurrentQuality = 0;
	}
	else
	{
		CurrentQuality--;
	}
	SetQuality(CurrentQuality);
}

void USettingItemWidget::OnClickNextButton()
{
	if (CurrentQuality >= 4)
	{
		CurrentQuality = 4;
	}
	else
	{
		CurrentQuality++;
	}

	SetQuality(CurrentQuality);
}

void USettingItemWidget::InitSettingType(EGameSettingsQuality InSetting)
{
	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		switch (InSetting)
		{
		case EGameSettingsQuality::FoliageQuality:
			{
				CurrentQuality = GSS->GetFoliageQuality();
				break;
			}
		case EGameSettingsQuality::ReflectionQuality:
			{
				CurrentQuality = GSS->GetReflectionQuality();
				break;
			}
		case EGameSettingsQuality::ShadingQuality:
			{
				CurrentQuality = GSS->GetShadingQuality();
				break;
			}
		case EGameSettingsQuality::ShadowQuality:
			{
				CurrentQuality = GSS->GetShadowQuality();
				break;
			}
		case EGameSettingsQuality::TextureQuality:
			{
				CurrentQuality = GSS->GetTextureQuality();
				break;
			}
		case EGameSettingsQuality::AntiAliasingQuality:
			{
				CurrentQuality = GSS->GetAntiAliasingQuality();
				break;
			}
		case EGameSettingsQuality::OverallScalabilityLevel:
			{
				CurrentQuality = GSS->GetOverallScalabilityLevel();
				break;
			}
		case EGameSettingsQuality::PostProcessingQuality:
			{
				CurrentQuality = GSS->GetPostProcessingQuality();
				break;
			}
		case EGameSettingsQuality::ViewDistanceQuality:
			{
				CurrentQuality = GSS->GetViewDistanceQuality();
				break;
			}
		case EGameSettingsQuality::VisualEffectQuality:
			{
				CurrentQuality = GSS->GetVisualEffectQuality();
				break;
			}

		default: break;
		}


		TextBlock_Quality->SetText(QualityValueToText(CurrentQuality));
	}
}


/**
 * 
 * @param InQuality 
 */
void USettingItemWidget::SetQuality(int32 InQuality)
{
	auto GSS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
	if (GSS)
	{
		if (SettingType == EGameSettingsQuality::OverallScalabilityLevel)
		{
			GSS->SetOverallScalabilityLevel(InQuality);
			GSS->OverallScalabilityChanged.Broadcast();
		}
		else
		{
			switch (SettingType)
			{
			case EGameSettingsQuality::FoliageQuality:
				{
					GSS->SetFoliageQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::ReflectionQuality:
				{
					GSS->SetReflectionQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::ShadingQuality:
				{
					GSS->SetShadingQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::ShadowQuality:
				{
					GSS->SetShadowQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::TextureQuality:
				{
					GSS->SetTextureQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::AntiAliasingQuality:
				{
					GSS->SetAntiAliasingQuality(InQuality);
					break;
				}

			case EGameSettingsQuality::PostProcessingQuality:
				{
					GSS->SetPostProcessingQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::ViewDistanceQuality:
				{
					GSS->SetViewDistanceQuality(InQuality);
					break;
				}
			case EGameSettingsQuality::VisualEffectQuality:
				{
					GSS->SetVisualEffectQuality(InQuality);
					break;
				}

			default: break;
			}

			GSS->OnCustomSettingChanged.Broadcast();
		}

		TextBlock_Quality->SetText(QualityValueToText(InQuality));
	}
}


/**========================================================================
 * 
 * 	0:low, 1:medium, 2:high, 3:epic, 4:cinematic
 * @param InQuality 
 * @return
 *
 * =========================================================================
 */
FText USettingItemWidget::QualityValueToText(int32 InQuality)
{
	FText QualityValueText;
	switch (InQuality)
	{
	case -1:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_custom", "custom");
			break;
		}
	case 0:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_low", "low");
			break;
		}
	case 1:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_medium", "medium");
			break;
		}
	case 2:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_high", "high");
			break;
		}
	case 3:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_epic", "epic");
			break;
		}
	case 4:
		{
			QualityValueText = NSLOCTEXT("i18Namespace", "i_cinematic", "cinematic");
			break;
		}

	default: break;
	}

	return QualityValueText;
}


FText USettingItemWidget::QualityNameToString(EGameSettingsQuality InQuality)
{
	FText SettingQualityText;


	switch (InQuality)
	{
	case EGameSettingsQuality::FoliageQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iFoliageQuality", "FoliageQuality");

			break;
		}
	case EGameSettingsQuality::ReflectionQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iReflectionQuality", "ReflectionQuality");
			break;
		}
	case EGameSettingsQuality::ShadingQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iShadingQuality", "ShadingQuality");
			break;
		}
	case EGameSettingsQuality::ShadowQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iShadowQuality", "ShadowQuality");
			break;
		}
	case EGameSettingsQuality::TextureQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iTextureQuality", "TextureQuality");
			break;
		}
	case EGameSettingsQuality::AntiAliasingQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iAntiAliasingQuality", "AntiAliasingQuality");
			break;
		}
	case EGameSettingsQuality::OverallScalabilityLevel:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iOverallScalabilityLevel", "OverallScalabilityLevel");
			break;
		}
	case EGameSettingsQuality::PostProcessingQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iPostProcessingQuality", "PostProcessingQuality");
			break;
		}
	case EGameSettingsQuality::ViewDistanceQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iViewDistanceQuality", "ViewDistanceQuality");
			break;
		}
	case EGameSettingsQuality::VisualEffectQuality:
		{
			SettingQualityText = NSLOCTEXT("i18Namespace", "iVisualEffectQuality", "VisualEffectQuality");
			break;
		}

	default: break;
	}
	return SettingQualityText;
}

void USettingItemWidget::OnOverallScalabilityChanged()
{
	InitSettingType(SettingType);
}

void USettingItemWidget::OnCustomSettingChanged()
{
	InitSettingType(SettingType);
}
