#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class CTEST_API ASpawnActor : public AActor
{
	GENERATED_BODY()
public:	
	ASpawnActor();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* SpawnBox;
	void Spawn();
    FTimerHandle TimerHandle;
};
