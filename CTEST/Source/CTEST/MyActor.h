#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

//새로운 카테고리를 만들 때 사용하는 매크로
DECLARE_LOG_CATEGORY_EXTERN(LogMyActor, Log, All);

UCLASS()


class CTEST_API AMyActor : public AActor
{
	GENERATED_BODY()
public:	
	AMyActor();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	void OnTimer();
	FTimerHandle TimerHandle;
	UStaticMeshComponent* StaticMesh;
	UMaterial* MyMat;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void TestFunction();
};
