// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "WindowModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API UWindowModeWidget : public UYtBaseWidget
{
	GENERATED_BODY()
	
	
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI|Window")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI|Window")
	void OnClickNextButton();

	void SetWindowMode();
public:
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* PreButton;


	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* TextBlock_WindowMode;

private:
	int32 ModeIndex;  // 0 1 2
	
};
