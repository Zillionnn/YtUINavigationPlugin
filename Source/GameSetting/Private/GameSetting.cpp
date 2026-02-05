// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameSetting.h"

#define LOCTEXT_NAMESPACE "FGameSettingModule"

void FGameSettingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FGameSettingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameSettingModule, GameSetting)