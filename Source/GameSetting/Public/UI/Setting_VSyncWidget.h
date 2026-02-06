// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "Setting_VSyncWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API USetting_VSyncWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CheckChanged(bool bIsChecked);

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();


	void InitSetting();

	void OnSettingChanged();

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI")
	UTextBlock* TextBlock_OnOff;

private:
	bool bVSyncOn;
};
