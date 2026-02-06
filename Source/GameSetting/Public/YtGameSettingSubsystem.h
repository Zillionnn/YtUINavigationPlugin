// Copyright (c) Yntoo, 2026
// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundGroups.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GenericPlatform/GenericWindow.h"
#include "YtGameSettingSubsystem.generated.h"

UENUM(BlueprintType)
enum EGameSettingsQuality
{
	PostProcessingQuality UMETA(DisplayName = "Post Processing Quality"),
	TextureQuality UMETA(DisplayName = "Texture Quality"),
	FoliageQuality UMETA(DisplayName = "Foliage Quality"),
	ShadowQuality UMETA(DisplayName = "Shadow Quality"),
	OverallScalabilityLevel UMETA(DisplayName = "Overall Scalability Level"),
	ShadingQuality UMETA(DisplayName = "Shading Quality"),
	ViewDistanceQuality UMETA(DisplayName = "View Distance Quality"),
	VisualEffectQuality UMETA(DisplayName = "Visual Effect Quality"),
	ReflectionQuality UMETA(DisplayName = "Reflection Quality"),
	AntiAliasingQuality UMETA(DisplayName = "Anti-Aliasing Quality")
};


DECLARE_MULTICAST_DELEGATE(FOverallScalabilityChanged);
DECLARE_MULTICAST_DELEGATE(FCustomSettingChanged);

/**
 * 
 */
UCLASS()
class GAMESETTING_API UYtGameSettingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, Category="YtGameSettings|Window")
	void SetWindowMode(EWindowMode::Type InMode);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings|Window")
	EWindowMode::Type GetWindowMode();


	UFUNCTION(BlueprintCallable, Category="YtGameSettings|Window")
	void SetScreenResolution(FIntPoint InXY);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings|Window")
	FIntPoint GetScreenResolution();


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetGameFrameLimit(float InFPS);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	float GetGameFrameLimit();

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetPresetSettings(int32 InQuality);


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetPostProcessingQuality(int32 InQuality);


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetTextureQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetFoliageQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetShadowQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetOverallScalabilityLevel(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetShadingQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetViewDistanceQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetVisualEffectQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetReflectionQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetAntiAliasingQuality(int32 InQuality);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetVSync(bool bEnable);

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetResolutionScale(float InValue);


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SetAntiAliasingMethod(int32 MethodNum);

	///////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetAntiAliasingQuality() const;


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetReflectionQuality() const;


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetTextureQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetFoliageQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetShadowQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetOverallScalabilityLevel() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetShadingQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetViewDistanceQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetVisualEffectQuality() const;

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetPostProcessingQuality();

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	bool GetVSync();

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	float GetResolutionScale();


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	int32 GetAntiAliasingMethod();

	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void RunHardwareBenchmark(int32 WorkScale, float CPUMultiplier, float GPUMultiplier);


	UFUNCTION(BlueprintCallable, Category="YtGameSettings")
	void SaveSettings();

	FOverallScalabilityChanged OverallScalabilityChanged;
	FCustomSettingChanged OnCustomSettingChanged;


	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	float GetMasterVolume();
	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	void SetMasterVolume(float InVolume);

	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	float GetBgmVolume();
	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	void SetBgmVolume(float InVolume);

	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	float GetEffectVolume();
	UFUNCTION(BlueprintCallable, Category="YtUI|Volume")
	void SetEffectVolume(float InVolume);


	void InitVolume(ESoundGroup InSoundGroup, float InVolume);


	UFUNCTION(BlueprintCallable, Category="other")
	void SaveYtGameSettings();
	void LoadGameSaveSettings();
private:
	int Quality;

	float CurrentMasterVolume = 1.0f;
	float CurrentSoundEffectVolume = 1.0f;
	float CurrentBgmVolume = 1.0f;
	FString SettingSaveSlotName;

};
