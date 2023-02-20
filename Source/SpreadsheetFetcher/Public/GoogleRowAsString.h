#pragma once

//### Get a single row as a simple string

#include "CoreMinimal.h"
#include "GoogleAsyncBase.h"
#include "GoogleRowAsString.generated.h"


UCLASS()
class UGoogleRowAsString : public UGoogleAsyncBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnRequestReceivedString OnResponse;
	
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, DisplayName= "Get Sheet Row as String", meta=(WorldContext="WorldContextObject"))
	static UGoogleRowAsString* AsyncTaskInit(UObject* WorldContextObject, FString ID, FString sheet, FString row);

	virtual void Activate() override;

	void OnHTTPRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	virtual void ParseSheetData(FHttpResponsePtr Response);

	FString ID;
	FString sheet;
	FString row;
	
public:
	
};