#include "GoogleAsyncBase.h"

const FString baseURL = "https://docs.google.com/spreadsheets/d/";
const FString formatURL = "/export?format=csv";

void UGoogleAsyncBase::Activate()
{
	Super::Activate();
}

FString UGoogleAsyncBase::BuildURL(FString ID, FString sheet = "", FString range = "")
{
	FString url = baseURL + ID + formatURL;
	
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

FHttpRequestRef UGoogleAsyncBase::CreateRequest(FString url)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(url);
	Request->SetVerb("GET");

	return Request;
}

