#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CTESTGameModeBase.generated.h"

UCLASS()
class CTEST_API ACTESTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACTESTGameModeBase();
protected:
	virtual void BeginPlay() override;
};
