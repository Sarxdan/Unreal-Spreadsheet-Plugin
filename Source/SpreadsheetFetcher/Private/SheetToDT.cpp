#include "SheetToDT.h"

//###
//### Sheet row to Data table
//###

USheetToDTRow* USheetToDTRow::AsyncTaskInitRow(UObject* WorldContextObject, FString ID, FString sheet,
	FString row, UDataTable* dataTable)
{
	USheetToDTRow* action = NewObject<USheetToDTRow>(WorldContextObject);
	action->ID = ID;
	action->sheet = sheet;
	action->row = row;
	action->dataTableRef = dataTable;

	return action;
}


void USheetToDTRow::Activate()
{
	Super::Activate();

	const FString url = Super::BuildURL(ID, sheet, "1:1");
	FHttpRequestPtr CategoryRequest = CreateRequest(url);
	CategoryRequest->OnProcessRequestComplete().BindUObject(this, &USheetToDTRow::OnHTTPRequestCompleteCategories);
	CategoryRequest->ProcessRequest();
}

void USheetToDTRow::OnHTTPRequestCompleteCategories(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	sheetData.Append(Response->GetContentAsString());

	const FString url = Super::BuildURL(ID, sheet, row + ":" + row);
	FHttpRequestPtr NewRequest = CreateRequest(url);
	NewRequest->OnProcessRequestComplete().BindUObject(this, &USheetToDTRow::OnHTTPRequestCompleteRow);
	NewRequest->ProcessRequest();
	
}

void USheetToDTRow::OnHTTPRequestCompleteRow(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bConnectedSuccessfully)
{
	sheetData.Append("\r\n" + Response->GetContentAsString());

	USheetToDTRow::AddToDataTable(Response);
}

void USheetToDTRow::AddToDataTable(FHttpResponsePtr Response)
{
	dataTableRef->EmptyTable();
	UDataTableFunctionLibrary::FillDataTableFromCSVString(dataTableRef, sheetData);
	OnResponse.Broadcast();
	
	FString rightSide, leftSide;
	Response->GetContentAsString().Split(",", &leftSide, &rightSide);
	
	OnResponse.Broadcast();
}

//###
//### Complete sheet to data table
//###

USheetToDT* USheetToDT::AsyncTaskInit(UObject* WorldContextObject, FString ID, FString sheet,
	UDataTable* dataTable)
{
	USheetToDT* action = NewObject<USheetToDT>(WorldContextObject);
	action->ID = ID;
	action->sheet = sheet;
	action->dataTableRef = dataTable;

	return action;
}

void USheetToDT::Activate()
{
	Super::Activate();

	const FString url = Super::BuildURL(ID, sheet);
	FHttpRequestPtr Request = CreateRequest(url);
	Request->OnProcessRequestComplete().BindUObject(this, &USheetToDT::OnHTTPRequestComplete);
	Request->ProcessRequest();
}

void USheetToDT::OnHTTPRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	USheetToDT::AddToDataTable(Response);
}

void USheetToDT::AddToDataTable(FHttpResponsePtr Response)
{

	dataTableRef->EmptyTable();
	UDataTableFunctionLibrary::FillDataTableFromCSVString(dataTableRef, Response->GetContentAsString());
	
	OnResponse.Broadcast();
	FString rightSide, leftSide;
	Response->GetContentAsString().Split(",", &leftSide, &rightSide);
	
	OnResponse.Broadcast();
}
