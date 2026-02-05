// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/YtBaseWidget.h"
#include "CultureWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class GAMESETTING_API UCultureWidget : public UYtBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickPreButton();

	UFUNCTION(BlueprintCallable, Category="YtUI")
	void OnClickNextButton();


	void ConfirmLanguage();

public:
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="#UI")
	// UButton* PreButton;
	//
	//
	// UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="#UI")
	// UButton* NextButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI|Widgets")
	UTextBlock* TextBlock_Culture;



private:
	int32 Index;
	FString Language;
	TArray<FString> LanguageList;
};
