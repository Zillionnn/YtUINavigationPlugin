// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSettingSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTING_API UGameSettingSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MasterVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float SoundEffectVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float BgmVolume = 1.0f;


	UGameSettingSaveGame();
	
};
