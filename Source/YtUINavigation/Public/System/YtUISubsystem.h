// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "YtUIGameInstance.h"
#include "YtUISubsystem.generated.h"

/**
 * 
 */
UCLASS()
class YTUINAVIGATION_API UYtUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="YtUI|Navigation")
	void RegisterWidgets();

	// 注册 Widget Class (在 editor 或代码里注册)
	void RegisterScreen(EUIScreen ScreenId, TSubclassOf<UUserWidget> WidgetClass);

	// 基本导航
	UFUNCTION(BlueprintCallable, Category="YtUI|Navigation")
	UUserWidget* ShowScreen(EUIScreen ScreenId); // Replace current (clear stack), like HUD

	UFUNCTION(BlueprintCallable, Category="YtUI|Navigation")
	UUserWidget* PushScreen(EUIScreen ScreenId); // Push onto stack

	UFUNCTION(BlueprintCallable, Category="YtUI|Navigation")
	void PopScreen(); // Pop top and show previous

	UFUNCTION(BlueprintCallable, Category="YtUI|Navigation")
	void PopAllAndShowMain();

	// helper
	UFUNCTION(BlueprintCallable, Category="YtUI|Input")
	void SetInputModeUI();

	UFUNCTION(BlueprintCallable, Category="YtUI|Input")
	void SetInputModeGame();

	void ClearWidgets();
	void EmptyWidget();

protected:
	// cache map & stack
	TMap<EUIScreen, TSubclassOf<UUserWidget>> RegisteredWidgets;

	// Using TWeakObjectPtr to avoid potential circular references and memory leaks
	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> WidgetStack;

	// create or get
	UUserWidget* CreateOrGetWidget(EUIScreen ScreenId);
	void ShowWidget(UUserWidget* Widget);
	void HideWidget(UUserWidget* Widget);
};