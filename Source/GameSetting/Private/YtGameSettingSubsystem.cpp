// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#include "YtGameSettingSubsystem.h"

#include "GameSettingSaveGame.h"
#include "YtUIGameInstance.h"
#include "Engine/RendererSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"
#include "Sound/SoundClass.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"


void UYtGameSettingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();

	// 读取存档
	SettingSaveSlotName = TEXT("YtGameSetting");
	LoadGameSaveSettings();


	// 图形质量
	int32 TextureQ = GameSetting->GetTextureQuality();
	UE_LOG(LogTemp, Warning, TEXT("texture quality  %d"), TextureQ);
}

void UYtGameSettingSubsystem::SetWindowMode(EWindowMode::Type InMode)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetFullscreenMode(InMode);
}

EWindowMode::Type UYtGameSettingSubsystem::GetWindowMode()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetFullscreenMode();
}

void UYtGameSettingSubsystem::SetScreenResolution(FIntPoint InXY)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetScreenResolution(InXY);
}

FIntPoint UYtGameSettingSubsystem::GetScreenResolution()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetScreenResolution();
}

void UYtGameSettingSubsystem::SetGameFrameLimit(float InFPS)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();

	// 限制FPS，降低GPU
	GameSetting->SetFrameRateLimit(InFPS);

	// GameSetting->SetResolutionScaleValueEx(20.0f);
}

float UYtGameSettingSubsystem::GetGameFrameLimit()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	const int32 framslimit = GameSetting->GetFrameRateLimit();

	return framslimit;
}

void UYtGameSettingSubsystem::SaveSettings()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->ApplySettings(true);
	GameSetting->SaveSettings();
}

float UYtGameSettingSubsystem::GetMasterVolume()
{
	return CurrentMasterVolume;
}

void UYtGameSettingSubsystem::SetMasterVolume(float InVolume)
{
	CurrentMasterVolume = InVolume;
}

float UYtGameSettingSubsystem::GetBgmVolume()
{
	return CurrentBgmVolume;
}

void UYtGameSettingSubsystem::SetBgmVolume(float InVolume)
{
	CurrentBgmVolume = InVolume;
}

float UYtGameSettingSubsystem::GetEffectVolume()
{
	return CurrentSoundEffectVolume;
}

void UYtGameSettingSubsystem::SetEffectVolume(float InVolume)
{
	CurrentSoundEffectVolume = InVolume;
}

/**
 * ====================================================
 * 从存档初始化音量
 * @param InSoundGroup 
 * @param InVolume
 * ====================================================
 */
void UYtGameSettingSubsystem::InitVolume(ESoundGroup InSoundGroup, float InVolume)
{
	auto GI = Cast<UYtUIGameInstance>(GetGameInstance());
	if (GI)
	{
		for (auto pair : GI->SoundGroups)
		{
			if (pair.Key == InSoundGroup)
			{
				if (pair.Value)
				{
					UGameplayStatics::SetSoundMixClassOverride(GetWorld(), GI->SoundMixClass, pair.Value, InVolume);
				}
			}
		}
		UGameplayStatics::PushSoundMixModifier(GetWorld(), GI->SoundMixClass);
	}
}

void UYtGameSettingSubsystem::SaveYtGameSettings()
{
	UGameSettingSaveGame* SaveGameInstance = Cast<UGameSettingSaveGame>(UGameplayStatics::CreateSaveGameObject(UGameSettingSaveGame::StaticClass()));

	// 设置全局数据
	SaveGameInstance->MasterVolume = GetMasterVolume();
	SaveGameInstance->SoundEffectVolume = GetEffectVolume();
	SaveGameInstance->BgmVolume = GetBgmVolume();


	// 保存到指定槽
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SettingSaveSlotName, 0);
}

void UYtGameSettingSubsystem::LoadGameSaveSettings()
{
	if (UGameSettingSaveGame* LoadedSave = Cast<UGameSettingSaveGame>(UGameplayStatics::LoadGameFromSlot(SettingSaveSlotName, 0)))
	{
		// 应用加载的数据
		CurrentMasterVolume = LoadedSave->MasterVolume;
		CurrentSoundEffectVolume = LoadedSave->SoundEffectVolume;
		CurrentBgmVolume = LoadedSave->BgmVolume;


		SetMasterVolume(CurrentMasterVolume);
		SetBgmVolume(CurrentBgmVolume);
		SetEffectVolume(CurrentSoundEffectVolume);

		FTimerDelegate Delegate = FTimerDelegate::CreateLambda([=, this]()
		{
			InitVolume(SOUNDGROUP_Default, CurrentMasterVolume);
			InitVolume(SOUNDGROUP_Effects, CurrentSoundEffectVolume);
			InitVolume(SOUNDGROUP_Music, CurrentBgmVolume);
		});
		FTimerHandle h;
		GetWorld()->GetTimerManager().SetTimer(h, Delegate, 1.0f, false);
	}
	else
	{
		// 没有找到存档，创建默认设置
		SaveYtGameSettings(); // 可选：保存默认值
	}
}


void UYtGameSettingSubsystem::SetPresetSettings(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();

	GameSetting->SetPostProcessingQuality(InQuality); // 0:low, 1:medium, 2:high, 3:epic, 4:cinematic (gets clamped if needed)
	GameSetting->SetTextureQuality(InQuality);
	GameSetting->SetFoliageQuality(InQuality);
	GameSetting->SetShadowQuality(InQuality);
	GameSetting->SetOverallScalabilityLevel(InQuality);
	GameSetting->SetShadingQuality(InQuality);
	GameSetting->SetViewDistanceQuality(InQuality);
	GameSetting->SetVisualEffectQuality(InQuality);


	// GameSetting->ApplySettings(true);
}

void UYtGameSettingSubsystem::SetPostProcessingQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetPostProcessingQuality(InQuality);
}

void UYtGameSettingSubsystem::SetTextureQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetTextureQuality(InQuality);
}

void UYtGameSettingSubsystem::SetFoliageQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetFoliageQuality(InQuality);
}

void UYtGameSettingSubsystem::SetShadowQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetShadowQuality(InQuality);
}

void UYtGameSettingSubsystem::SetOverallScalabilityLevel(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetOverallScalabilityLevel(InQuality);
}

void UYtGameSettingSubsystem::SetShadingQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetShadingQuality(InQuality);
}

void UYtGameSettingSubsystem::SetViewDistanceQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetViewDistanceQuality(InQuality);
}

void UYtGameSettingSubsystem::SetVisualEffectQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetVisualEffectQuality(InQuality);
}

void UYtGameSettingSubsystem::SetReflectionQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetReflectionQuality(InQuality);
}

void UYtGameSettingSubsystem::SetAntiAliasingQuality(int32 InQuality)
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	GameSetting->SetAntiAliasingQuality(InQuality);
}

void UYtGameSettingSubsystem::SetVSync(bool bEnable)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (UserSettings)
	{
		UserSettings->SetVSyncEnabled(bEnable);
	}
}

void UYtGameSettingSubsystem::SetResolutionScale(float InValue)
{
	if (GEngine)
	{
		// 方法二：通过 UGameUserSettings
		UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
		if (UserSettings)
		{
			UserSettings->SetResolutionScaleValueEx(InValue);
		}
	}
}

void UYtGameSettingSubsystem::SetAntiAliasingMethod(int32 MethodNum)
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), FString::Printf(TEXT("r.AntiAliasingMethod %d"), MethodNum));

	URendererSettings* RendererSettings = GetMutableDefault<URendererSettings>();
	RendererSettings->DefaultFeatureAntiAliasing = static_cast<EAntiAliasingMethod>(MethodNum);
}


int32 UYtGameSettingSubsystem::GetAntiAliasingQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetAntiAliasingQuality();
}

int32 UYtGameSettingSubsystem::GetReflectionQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetReflectionQuality();
}

int32 UYtGameSettingSubsystem::GetTextureQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetTextureQuality();
}

int32 UYtGameSettingSubsystem::GetFoliageQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetFoliageQuality();
}

int32 UYtGameSettingSubsystem::GetShadowQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetShadowQuality();
}

int32 UYtGameSettingSubsystem::GetOverallScalabilityLevel() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetOverallScalabilityLevel();
}

int32 UYtGameSettingSubsystem::GetShadingQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetShadingQuality();
}

int32 UYtGameSettingSubsystem::GetViewDistanceQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetViewDistanceQuality();
}

int32 UYtGameSettingSubsystem::GetVisualEffectQuality() const
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetVisualEffectQuality();
}

int32 UYtGameSettingSubsystem::GetPostProcessingQuality()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->GetPostProcessingQuality();
}

bool UYtGameSettingSubsystem::GetVSync()
{
	UGameUserSettings* GameSetting = UGameUserSettings::GetGameUserSettings();
	return GameSetting->IsVSyncEnabled();
}

float UYtGameSettingSubsystem::GetResolutionScale()
{
	float PercentCVar = 0.0f;
	// 1. UGameUserSettings 获取
	if (GEngine)
	{
		UGameUserSettings* Settings = GEngine->GetGameUserSettings();
		if (Settings)
		{
			float Normalized = Settings->GetResolutionScaleNormalized();
			PercentCVar = Normalized * 100.0f;
			if (PercentCVar < 1.0f)
			{
				SetResolutionScale(100.f);
			}
			UE_LOG(LogTemp, Log, TEXT("UGS Resolution Scale: %.1f%%"), PercentCVar);
		}
	}

	// 2. 控制台变量获取
	// if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.ScreenPercentage")))
	// {
	// 	PercentCVar = CVar->GetFloat();
	// 	UE_LOG(LogTemp, Log, TEXT("Console Var r.ScreenPercentage: %.1f%%"), PercentCVar);
	// }

	return PercentCVar;
}

int32 UYtGameSettingSubsystem::GetAntiAliasingMethod()
{
	URendererSettings* RendererSettings = GetMutableDefault<URendererSettings>();
	UE_LOG(LogTemp, Log, TEXT("%s %d"), *FString(__FUNCTION__), static_cast<int32>(RendererSettings->DefaultFeatureAntiAliasing));
	return RendererSettings->DefaultFeatureAntiAliasing;
}

/**
 * ==================================================
 * 自动使用最佳配置
 * ==================================================
 */
void UYtGameSettingSubsystem::RunHardwareBenchmark(int32 WorkScale, float CPUMultiplier, float GPUMultiplier)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (UserSettings)
	{
		// 运行基准测试（异步操作，可能需要等待完成）
		UserSettings->RunHardwareBenchmark(WorkScale, CPUMultiplier, GPUMultiplier);
		UserSettings->ApplyHardwareBenchmarkResults();

		OnCustomSettingChanged.Broadcast();
		OverallScalabilityChanged.Broadcast();
		UserSettings->ApplySettings(true);
	}
}
