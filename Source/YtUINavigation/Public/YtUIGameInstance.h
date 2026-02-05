// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Templates/SubclassOf.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundGroups.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "YtUIGameInstance.generated.h"


UENUM(BlueprintType)
enum class EUIScreen : uint8
{
	MainMenu,
	Settings,
	StartGameConfirm,
	InGameHUD,
	PauseMenu,
	LoadingScreen,
	LevelSelection,
	LevelResult
	// add more...
};


/**
 * 
 */
UCLASS()
class YTUINAVIGATION_API UYtUIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="UISetting")
	TMap<EUIScreen, TSubclassOf<UUserWidget>> WidgetToRegister;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Audio")
	TMap<TEnumAsByte<ESoundGroup>, USoundClass*> SoundGroups;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Audio")
	USoundMix* SoundMixClass;

protected:
	virtual void Init() override;
	virtual void Shutdown() override;

	void OnWorldBeginTearDown(UWorld* World);
	void BeginLoadMap(const FString& MapName);
	void EndLoadMap(UWorld* LoadedWorld);

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	// loading widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMGGame")
	TSubclassOf<UUserWidget> LoadingWidget;

private:
	FDelegateHandle WorldTearDownHandle;
};
