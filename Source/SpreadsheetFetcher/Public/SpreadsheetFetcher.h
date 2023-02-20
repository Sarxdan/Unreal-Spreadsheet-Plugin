// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ImportToDT.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"

#include "Modules/ModuleManager.h"

class FSpreadsheetFetcherModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	
};
