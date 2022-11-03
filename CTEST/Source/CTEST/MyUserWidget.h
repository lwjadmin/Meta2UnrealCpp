// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


UCLASS()
class CTEST_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void OnClicked();

	UFUNCTION()
	void OnEndAnim();
};
