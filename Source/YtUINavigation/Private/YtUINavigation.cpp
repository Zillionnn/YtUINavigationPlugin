// Copyright (c) Yntoo, 2026
//  All Rights Reserved.

#include "YtUINavigation.h"

#define LOCTEXT_NAMESPACE "FYtUINavigationModule"

void FYtUINavigationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FYtUINavigationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYtUINavigationModule, YtUINavigation)