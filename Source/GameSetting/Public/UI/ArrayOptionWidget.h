// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/YtBaseWidget.h"
#include "ArrayOptionWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOptionChanged, FText, Option);

/**
 * 
 */
UCLASS()
class GAMESETTING_API UArrayOptionWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();

	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="#UI")
	// UButton* PreButton;
	//
	//
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="#UI")
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* TextBlock_CurrentOption;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="YtUI|Options")
	TArray<FString> OptionList;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category="YtUI|Events")
	FOptionChanged OptionChanged;

private:
	int Index;
};
