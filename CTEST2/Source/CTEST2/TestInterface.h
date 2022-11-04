// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "UObject/Interface.h"
#include "TestInterface.generated.h"

/*------------------------------------------------------------------------------
	※ 인터페이스
	  인터페이스를 통해 다른 객체가 공통 기능을 공유할 수 있지만, 
	  필요한 경우 객체가 해당 기능을 다르게 처리할 수 있습니다.
 ------------------------------------------------------------------------------*/
UINTERFACE(BlueprintType)
class CTEST2_API UTestInterface : public UInterface
{
	GENERATED_BODY()
};

class CTEST2_API ITestInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallInterface();
};
