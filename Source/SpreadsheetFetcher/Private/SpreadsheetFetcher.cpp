// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpreadsheetFetcher.h"
#include "LevelEditor.h"
#include "ContentBrowserModule.h"
#include "ContentBrowserDelegates.h"
#include "Runtime/Engine/Classes/Kismet/DataTableFunctionLibrary.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"

#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"

#define LOCTEXT_NAMESPACE "FSpreadsheetFetcherModule"

void FSpreadsheetFetcherModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSpreadsheetFetcherModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpreadsheetFetcherModule, SpreadsheetFetcher)