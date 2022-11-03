// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget2.generated.h"

/**
 * 
 */
UCLASS()
class CTEST_API UMyUserWidget2 : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnBtnStartClicked();

	UFUNCTION()
	void OnBtnExitClicked();
	
};
