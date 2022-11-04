// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CTEST2GameModeBase.generated.h"



UCLASS()
class CTEST2_API ACTEST2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
