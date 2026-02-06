// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/YtBaseWidget.h"
#include "Setting_AntiAliasingMethodWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class GAMESETTING_API USetting_AntiAliasingMethodWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void InitMethod(int32 InMethod);

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="YtUI")
	void SetAntialiasingMethod(int32 InMethod);

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI")
	UTextBlock* TextBlock_AntiMethod;

private:
	int32 CurrentMethod;
	TArray<int32> MethodArray;
	int32 MethodIndex;
};
