// Copyright (c) Yntoo, 2026
// All Rights Reserved.
#pragma once

#include "Modules/ModuleManager.h"

class FYtUINavigationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
