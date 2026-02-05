// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateTypes.h"
#include "Layout/Margin.h"
#include "UIStyleData.generated.h"

/**
 * 
 */
UCLASS()
class YTUINAVIGATION_API UUIStyleData : public UDataAsset
{
	GENERATED_BODY()

public:
	// 按钮相关
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
	UTexture2D* ButtonBackgroundTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
	FLinearColor ButtonTint = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
	FLinearColor ButtonHoverTint = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	FButtonStyle ButtonStyle;

	// 文本相关
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	TObjectPtr<const UObject> UIFont;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	int32 FontSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	FLinearColor TextColor = FLinearColor::White;

	// 其他通用数值（可扩展）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Common")
	FMargin ButtonPadding = FMargin(6.f);
};
