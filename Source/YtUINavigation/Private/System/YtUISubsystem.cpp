// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#include "System/YtUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UYtUISubsystem::RegisterWidgets()
{
	auto GI = Cast<UYtUIGameInstance>(GetWorld()->GetGameInstance());

	if (GI)
	{
		/////////////////////////////////////////////////////
		/// register widgets
		for (auto pair : GI->WidgetToRegister)
		{
			RegisterScreen(pair.Key, pair.Value);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance is not UYtUIGameInstance type"));
	}
}

void UYtUISubsystem::RegisterScreen(EUIScreen ScreenId, TSubclassOf<UUserWidget> WidgetClass)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Registering screen: %d with widget class: %s"), *FString(__FUNCTION__), static_cast<uint8>(ScreenId), WidgetClass ? *WidgetClass->GetName() : TEXT("nullptr"));
	if (WidgetClass)
	{
		RegisteredWidgets.Add(ScreenId, WidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Attempting to register null widget class for screen: %d"), *FString(__FUNCTION__), static_cast<uint8>(ScreenId));
	}
}

/**
 * ====================================================
 * 获取widget，如果没有就创建
 * @param ScreenId 
 * @return
 * ====================================================
 */
UUserWidget* UYtUISubsystem::CreateOrGetWidget(EUIScreen ScreenId)
{
	TSubclassOf<UUserWidget>* ClassPtr = RegisteredWidgets.Find(ScreenId);
	if (!ClassPtr || !(*ClassPtr))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] No widget class registered for screen: %d"), *FString(__FUNCTION__), static_cast<uint8>(ScreenId));
		return nullptr;
	}

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Invalid world"), *FString(__FUNCTION__));
		return nullptr;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] No player controller found"), *FString(__FUNCTION__));
		return nullptr;
	}

	UUserWidget* Widget = CreateWidget<UUserWidget>(PC, *ClassPtr);
	return Widget;
}

/**
 * ====================================================
 * remove all widget , add a new widget
 * 移除所有widget ， 创建1个widget到屏幕
 * @param ScreenId 
 * @return
 * ====================================================
 */
UUserWidget* UYtUISubsystem::ShowScreen(EUIScreen ScreenId)
{
	// Hide all widgets in stack
	for (UUserWidget* W : WidgetStack)
	{
		if (IsValid(W))
		{
			HideWidget(W);
		}
	}
	WidgetStack.Empty();

	UUserWidget* Widget = CreateOrGetWidget(ScreenId);
	if (IsValid(Widget))
	{
		ShowWidget(Widget);
		WidgetStack.Push(Widget);
	}
	return Widget;
}

/**
 * ====================================================
 * remove top widget, add new widget
 * 移除顶部的widget，添加1个新的widget 
 * @param ScreenId 
 * @return
 * ====================================================
 */
UUserWidget* UYtUISubsystem::PushScreen(EUIScreen ScreenId)
{
	// hide current top (but keep in stack)
	if (WidgetStack.Num() > 0)
	{
		UUserWidget* CurrentTop = WidgetStack.Last();
		if (IsValid(CurrentTop))
		{
			HideWidget(CurrentTop);
		}
	}

	UUserWidget* Widget = CreateOrGetWidget(ScreenId);
	if (IsValid(Widget))
	{
		ShowWidget(Widget);
		WidgetStack.Push(Widget);
		SetInputModeUI();
	}
	return Widget;
}

/**
 * ====================================================
 * remove top widgetA, and show widgetB which under widgetA
 * 移除顶部widgetA，显示出widgetA底下的widgetB
 * ====================================================
 */
void UYtUISubsystem::PopScreen()
{
	if (WidgetStack.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Widget stack is empty, nothing to pop"), *FString(__FUNCTION__));
		return;
	}

	UUserWidget* Top = WidgetStack.Pop();
	if (IsValid(Top))
	{
		HideWidget(Top);
		// Remove the widget from the array to ensure proper cleanup
		Top = nullptr;
	}

	if (WidgetStack.Num() > 0)
	{
		UUserWidget* NewTop = WidgetStack.Last();
		if (IsValid(NewTop))
		{
			ShowWidget(NewTop);
			SetInputModeUI();
		}
	}
	else
	{
		// no UI -> switch to game input
		SetInputModeGame();
	}
}

void UYtUISubsystem::PopAllAndShowMain()
{
	while (WidgetStack.Num() > 0)
	{
		UUserWidget* W = WidgetStack.Pop();
		if (IsValid(W))
		{
			HideWidget(W);
		}
	}

	// Clear the stack to ensure it's completely empty
	WidgetStack.Empty();
	
	ShowScreen(EUIScreen::MainMenu);
}

void UYtUISubsystem::SetInputModeUI()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Invalid world"), *FString(__FUNCTION__));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] No player controller found"), *FString(__FUNCTION__));
		return;
	}

	PC->bShowMouseCursor = true;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Optionally set focus widget:
	// if (WidgetStack.Num()>0 && WidgetStack.Last()->TakeWidget().IsValid()) InputMode.SetWidgetToFocus(WidgetStack.Last()->TakeWidget());
	PC->SetInputMode(InputMode);
}

void UYtUISubsystem::SetInputModeGame()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Invalid world"), *FString(__FUNCTION__));
		return;
	}
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] No player controller found"), *FString(__FUNCTION__));
		return;
	}

	PC->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	PC->SetInputMode(InputMode);
}

void UYtUISubsystem::ClearWidgets()
{
	while (WidgetStack.Num() > 0)
	{
		UUserWidget* W = WidgetStack.Pop();
		if (IsValid(W))
		{
			HideWidget(W);
		};
	}

	WidgetStack.Empty();
}

void UYtUISubsystem::EmptyWidget()
{
	// Hide any visible widgets before clearing the stack
	for (UUserWidget* W : WidgetStack)
	{
		if (IsValid(W))
		{
			HideWidget(W);
		}
	}
	
	WidgetStack.Empty();
}

void UYtUISubsystem::ShowWidget(UUserWidget* Widget)
{
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Trying to show null widget"), *FString(__FUNCTION__));
		return;
	}
	
	if (!Widget->IsInViewport())
	{
		Widget->AddToViewport(100); // use z-order
	}
	Widget->SetVisibility(ESlateVisibility::Visible);
}

void UYtUISubsystem::HideWidget(UUserWidget* Widget)
{
	if (!IsValid(Widget))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Trying to hide invalid widget"), *FString(__FUNCTION__));
		return;
	}
	
	// Widget->SetVisibility(ESlateVisibility::Collapsed);
	// optionally remove from parent to free memory:	
	Widget->RemoveFromParent();
}