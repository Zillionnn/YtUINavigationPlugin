// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "ResolutionScaleWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API UResolutionScaleWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable, Category="YtUI")
	void Decrease(float Value);

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void Increase(float Value);

	void SetScreenPercentage();
	float GetScreenPercentage();

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* Text_ResolutionScaleValue;

private:
	float ScreenPercentage;
	float MaxScreenPercentage;
	float MinScreenPercentage;
};
