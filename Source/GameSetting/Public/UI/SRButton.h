// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SRButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSRButtonClickedEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSRButtonPressEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSRButtonReleaseEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSRButtonFocus, UUserWidget*, SRButton);

/**
 * 
 */
UCLASS()
class GAMESETTING_API USRButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;


	UFUNCTION()
	void OnClick();


	UFUNCTION()
	void OnPress();

	UFUNCTION()
	void OnRelease();

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI")
	UButton* SRButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="YtUI")	
	UTextBlock* TextBlock;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="YtUI|Button")
	FText Text;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="YtUI|Events")
	FOnSRButtonClickedEvent OnButtonClicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="YtUI|Events")
	FOnSRButtonPressEvent OnButtonPress;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="YtUI|Events")
	FOnSRButtonReleaseEvent OnButtonRelease;

	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, BlueprintCallable, Category="YtUI|Events")
	FOnSRButtonFocus OnFocus;
	void SetButtonText(FString InText);
};
