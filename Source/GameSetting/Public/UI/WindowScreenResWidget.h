// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "WindowScreenResWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API UWindowScreenResWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();

	void SetResolution(FIntPoint InPoint);

public:
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* PreButton;


	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* TextBlock_ScreenRes;

private:
	int32 ModeIndex; // 0 1 2
	TArray<FIntPoint> ResolutionList;
	FIntPoint ScreenRes;
};
