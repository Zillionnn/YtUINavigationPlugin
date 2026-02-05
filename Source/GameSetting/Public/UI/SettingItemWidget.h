// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YtGameSettingSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UI/YtBaseWidget.h"
#include "SettingItemWidget.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class GAMESETTING_API USettingItemWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();


	UFUNCTION(BlueprintCallable, Category="YtUI")
	void InitSettingType(EGameSettingsQuality InSetting);

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void SetQuality(int32 InQuality);

	FText QualityValueToText(int32 InQuality);
	FText QualityNameToString(EGameSettingsQuality InQuality);


	void OnOverallScalabilityChanged();
	void OnCustomSettingChanged();

public:
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* PreButton;
	//
	//
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtSetting")
	UTextBlock* TextBlock_QualityName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtSetting")
	UTextBlock* TextBlock_Quality;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="YtSetting")
	TEnumAsByte<EGameSettingsQuality> SettingType;

private:
	int32 CurrentQuality;

	//  0:low, 1:medium, 2:high, 3:epic, 4:cinematic
	int32 MaxQuality = 4;
	int32 MinQuality = 0;
};
