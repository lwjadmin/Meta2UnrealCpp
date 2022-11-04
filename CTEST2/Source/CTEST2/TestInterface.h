// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "UObject/Interface.h"
#include "TestInterface.generated.h"

/*------------------------------------------------------------------------------
	�� �������̽�
	  �������̽��� ���� �ٸ� ��ü�� ���� ����� ������ �� ������, 
	  �ʿ��� ��� ��ü�� �ش� ����� �ٸ��� ó���� �� �ֽ��ϴ�.
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
