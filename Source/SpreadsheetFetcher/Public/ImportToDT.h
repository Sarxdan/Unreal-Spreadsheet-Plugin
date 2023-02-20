#pragma once

//### 

#include "Http.h"

#include "ImportToDT.generated.h"

DECLARE_DELEGATE_OneParam(OnResponse, FString);

UCLASS()
class UImportToDT : public UObject
{
	GENERATED_BODY()



	static FString BuildURL(FString ID, FString sheet, FString range);
	static FHttpRequestRef CreateRequest(FString url);

	void OnHTTPRequestCompleteRow(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnHTTPRequestCompleteCategories(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	FString sheetData;

	FString ID;
	FString sheet;
	FString range;
	
public:

	OnResponse OnResponseDelegate;
	
	void LoadFromSpreadsheet(FString ID, FString Sheetname, FString Range);
	
};
