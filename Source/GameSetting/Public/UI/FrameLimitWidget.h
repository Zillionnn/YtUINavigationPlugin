// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/YtBaseWidget.h"
#include "FrameLimitWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class GAMESETTING_API UFrameLimitWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();

public:
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* PreButton;


	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* TextBlock_FPS;



public:
	void SetFPS(float InFPS);
private:
	int32 FPSIndex;
	float CurrentFPS;
	TArray<float> FPSArray;
	
};
