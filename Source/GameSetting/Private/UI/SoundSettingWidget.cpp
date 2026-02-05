// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SoundSettingWidget.h"

#include "YtGameSettingSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"


void USoundSettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USoundSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Volume = 1.0f;
	MaxVolume = 1.0f;
	MinVolume = 0.01f;

	// Slider_Volume->OnValueChanged.AddDynamic(this, &USoundSettingWidget::ChangeVolume);
}

void USoundSettingWidget::ChangeVolume(float Value)
{
	Volume = Value;
	if (SoundMixClass && SoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixClass, SoundClass, Value);

		FString VolumeString = FString::Printf(TEXT("%d"), static_cast<int>(Value * 100));
		Text_SoundValue->SetText(FText::FromString(VolumeString));
	}
}

void USoundSettingWidget::DecreaseVolume(float Value)
{
	Volume -= Value;
	if (Volume <= MinVolume)
	{
		Volume = MinVolume;
	}
	SetVolume();
}

void USoundSettingWidget::IncreaseVolume(float Value)
{
	Volume += Value;
	if (Volume >= MaxVolume)
	{
		Volume = MaxVolume;
	}
	SetVolume();
}


void USoundSettingWidget::SetVolume_Implementation()
{
	if (SoundMixClass && SoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixClass, SoundClass, Volume);

		FString VolumeString = FString::Printf(TEXT("%d"), static_cast<int>(Volume * 100));
		Text_SoundValue->SetText(FText::FromString(VolumeString));

		auto YGS = GetGameInstance()->GetSubsystem<UYtGameSettingSubsystem>();
		if (YGS)
		{
			switch (SoundGroup)
			{
			case SOUNDGROUP_Default:
				{
					YGS->SetMasterVolume(Volume);
					break;
				}
			case SOUNDGROUP_Music:
				{
					YGS->SetBgmVolume(Volume);
					break;
				}
			case SOUNDGROUP_Effects:
				{
					YGS->SetEffectVolume(Volume);
					break;
				}
			default: break ;
			}
		}
	}
}

float USoundSettingWidget::GetVolume()
{
	return Volume;
}
