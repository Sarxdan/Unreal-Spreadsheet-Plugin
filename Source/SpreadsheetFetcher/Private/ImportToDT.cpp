#include "ImportToDT.h"

void UImportToDT::LoadFromSpreadsheet(FString IDin, FString SheetName, FString Range)
{
	ID = IDin;
	sheet = SheetName;
	range = Range;
		
	if(!range.IsEmpty())
	{
		const FString url = BuildURL(ID, sheet, "1:1");
		FHttpRequestPtr CategoryRequest = CreateRequest(url);
		CategoryRequest->OnProcessRequestComplete().BindUObject(this, &UImportToDT::OnHTTPRequestCompleteRow);
		CategoryRequest->ProcessRequest();
	}
	else
	{
		const FString url = BuildURL(ID, sheet, range);
		FHttpRequestPtr CategoryRequest = CreateRequest(url);
		CategoryRequest->OnProcessRequestComplete().BindUObject(this, &UImportToDT::OnHTTPRequestCompleteCategories);
		CategoryRequest->ProcessRequest();
	}
	
}

FString UImportToDT::BuildURL(FString ID, FString sheet = "", FString range = "")
{
	FString url = "https://docs.google.com/spreadsheets/d/" + ID + "/export?format=csv";
	
	if(sheet != "")
	{
		url += "&sheet=" + sheet;
	}
	if(range != "" && range != ":")
	{
		url += "&range=" + range;
	}
	
	return url;
}

FHttpRequestRef UImportToDT::CreateRequest(FString url)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(url);
	Request->SetVerb("GET");

	return Request;
}


void UImportToDT::OnHTTPRequestCompleteCategories(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	sheetData.Append(Response->GetContentAsString());

	const FString url = BuildURL(ID, sheet, range);
	FHttpRequestPtr NewRequest = CreateRequest(url);
	NewRequest->OnProcessRequestComplete().BindUObject(this, &UImportToDT::OnHTTPRequestCompleteRow);
	NewRequest->ProcessRequest();
	
}

void UImportToDT::OnHTTPRequestCompleteRow(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bConnectedSuccessfully)
{
	sheetData.Append("\r\n" + Response->GetContentAsString());
	
	OnResponseDelegate.ExecuteIfBound(sheetData);
}

