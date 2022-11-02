// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THRIRDPERSONCPP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Status")
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status" meta=(DisplayName="IsInAir", ScriptName="IsInAir"))
	//bool bIsInAir = false;
	uint32 bIsInAir : 1;

};
