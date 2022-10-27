#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerTest.generated.h"

UCLASS()
class CTEST_API ATimerTest : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimerTest();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* CountDownText;
	UPROPERTY(EditAnywhere)
	int32 CountDown;
	FTimerHandle TimerHandle;
	void TimerCountDown();
	void UpdateTimerDisplay();
	void AdvanceTimer();

	/*-----------------------------------------------------------------
	BlueprintNativeEvent : �������Ʈ���� �Լ� �������̵�(������) ���� 
	-----------------------------------------------------------------*/
	UFUNCTION(BlueprintNativeEvent)
	void CountDownHasFinished();
};
