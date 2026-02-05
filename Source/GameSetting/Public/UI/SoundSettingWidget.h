// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundGroups.h"
#include "SoundSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API USoundSettingWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void ChangeVolume(float Value);


	UFUNCTION(BlueprintCallable, Category="YtUI")
	void DecreaseVolume(float Value);


	UFUNCTION(BlueprintCallable, Category="YtUI")
	void IncreaseVolume(float Value);

	UFUNCTION(BlueprintNativeEvent, Category="YtUI|Audio")
	void SetVolume();

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* Text_SoundValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="YtUI|Audio")
	TEnumAsByte<ESoundGroup> SoundGroup;

	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// USlider* Slider_Volume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="YtUI|Audio")
	USoundMix* SoundMixClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="YtUI|Audio")
	USoundClass* SoundClass;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	float GetVolume();
private:
	float Volume;
	float MaxVolume;
	float MinVolume;
};
