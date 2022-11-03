// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent2.generated.h"

/*--------------------------------------------------------------
	커스텀 컴포넌트 만들기!!

	BlueprintSpawnableComponent : 존재하면, 블루프린트가 컴포넌트 클래스를 스폰시킬 수 있습니다.
--------------------------------------------------------------*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CTEST_API UMyActorComponent2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetFollowTarget(AActor* target, float speed);

	AActor* FollowTarget;
	float FollowSpeed;
	
};
