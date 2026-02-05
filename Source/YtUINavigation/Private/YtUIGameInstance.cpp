// Fill out your copyright notice in the Description page of Project Settings.


#include "YtUIGameInstance.h"

#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"


void UYtUIGameInstance::Init()
{
	Super::Init();

	//PreLoadMap，开始加载map
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UYtUIGameInstance::BeginLoadMap);
	//PostLoadMapWithWorld， 加载完成后
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UYtUIGameInstance::EndLoadMap);
	WorldTearDownHandle = FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UYtUIGameInstance::OnWorldBeginTearDown);
}

void UYtUIGameInstance::Shutdown()
{
	if (WorldTearDownHandle.IsValid())
	{
		FWorldDelegates::OnWorldBeginTearDown.Remove(WorldTearDownHandle);
		WorldTearDownHandle.Reset();
	}
	Super::Shutdown();
}

void UYtUIGameInstance::OnWorldBeginTearDown(UWorld* World)
{
	// auto UIS = GetWorld()->GetSubsystem<UYtUISubsystem>();
	// if (UIS)
	// {
	// 	// UIS->ClearWidgets();
	// }
}

void UYtUIGameInstance::BeginLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreen;

	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.bWaitForManualStop = false;
	LoadingScreen.bMoviesAreSkippable = false;
	LoadingScreen.MinimumLoadingScreenDisplayTime = 1.5f; // movie最少播放时间

	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget(); // movie不存在时，显示的widget

	if (LoadingWidget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, LoadingWidget);
		TSharedPtr<SWidget> LoadScreen = CurrentWidget->TakeWidget();
		LoadingScreen.WidgetLoadingScreen = LoadScreen;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadingWidget == nullptr"));
	}

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	// auto UIS = GetWorld()->GetSubsystem<UYtUISubsystem>();
	// if (UIS)
	// {
	// 	UIS->EmptyWidget();
	// }
}

void UYtUIGameInstance::EndLoadMap(UWorld* LoadedWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("end load map"));
}

void UYtUIGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
}

void UYtUIGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
}
