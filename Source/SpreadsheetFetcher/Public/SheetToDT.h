#pragma once

#include "CoreMinimal.h"
#include "GoogleAsyncBase.h"
#include "GoogleAsyncBase.h"
#include "Engine/DataTable.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "SheetToDT.generated.h"
// ### Wrappers for importing spreadsheet to data table

//###
//### Sheet row to Data table
//###

UCLASS()
class USheetToDTRow : public UGoogleAsyncBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnRequestReceived OnResponse;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, DisplayName= "Import Row to DataTable", meta=(WorldContext="WorldContextObject"))
	static USheetToDTRow* AsyncTaskInitRow(UObject* WorldContextObject, FString ID, FString sheet, FString row, UDataTable* dataTable);
	
	virtual void Activate() override;

	void OnHTTPRequestCompleteRow(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnHTTPRequestCompleteCategories(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	virtual void AddToDataTable(FHttpResponsePtr Response);

	FString ID;
	FString sheet;
	FString row;

	FString sheetData;
	UDataTable* dataTableRef;
	
};

//###
//### Complete sheet to data table
//###

UCLASS()
class USheetToDT : public UGoogleAsyncBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnRequestReceived OnResponse;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, DisplayName= "Import Sheet to DataTable", meta=(WorldContext="WorldContextObject"))
	static USheetToDT* AsyncTaskInit(UObject* WorldContextObject, FString ID, FString sheet, UDataTable* dataTable);

	virtual void Activate() override;

	void OnHTTPRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	virtual void AddToDataTable(FHttpResponsePtr Response);

	FString ID;
	FString sheet;
	FString row;

	UDataTable* dataTableRef;
	FString data;
	
public:
	
};