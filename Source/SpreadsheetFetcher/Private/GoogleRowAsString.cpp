#include "GoogleRowAsString.h"

UGoogleRowAsString* UGoogleRowAsString::AsyncTaskInit(UObject* WorldContextObject, FString ID, FString sheet = "",
	FString row = "1")
{
	UGoogleRowAsString* action = NewObject<UGoogleRowAsString>(WorldContextObject);
	action->ID = ID;
	action->sheet = sheet;
	action->row = row;

	return action;
}

void UGoogleRowAsString::Activate()
{
	Super::Activate();

	const FString url = Super::BuildURL(ID, sheet, row + ":" + row);
	FHttpRequestPtr Request = CreateRequest(url);
	Request->OnProcessRequestComplete().BindUObject(this, &UGoogleRowAsString::OnHTTPRequestComplete);
	Request->ProcessRequest();
}

void UGoogleRowAsString::OnHTTPRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UGoogleRowAsString::ParseSheetData(Response);
}

void UGoogleRowAsString::ParseSheetData(FHttpResponsePtr Response)
{
	FString rightSide, leftSide;
	Response->GetContentAsString().Split(",", &leftSide, &rightSide);
	OnResponse.Broadcast(rightSide);
}
