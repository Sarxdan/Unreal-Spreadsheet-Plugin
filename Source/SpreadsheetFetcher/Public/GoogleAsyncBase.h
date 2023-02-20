#pragma once

//### Create HTTP requests

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "GoogleAsyncBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestReceivedString, FString, response);

UCLASS()
class UGoogleAsyncBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	
protected:

	static FString BuildURL(FString ID, FString sheet, FString range);
	static FHttpRequestRef CreateRequest(FString url);
	

	virtual void Activate() override;
	
};
