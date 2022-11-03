// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

UENUM(BlueprintType)
enum class ELevel : uint8
{
	Unknown = 0,
	MenuLevel = 1,
	GameLevel = 2
};

/**
 * 
 */
UCLASS()
class CTEST_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ELevel CurrentLevel = ELevel::Unknown;
protected:
	virtual void BeginPlay() override;
};
