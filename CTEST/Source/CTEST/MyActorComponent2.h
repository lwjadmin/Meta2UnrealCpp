// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent2.generated.h"

/*--------------------------------------------------------------
	Ŀ���� ������Ʈ �����!!

	BlueprintSpawnableComponent : �����ϸ�, �������Ʈ�� ������Ʈ Ŭ������ ������ų �� �ֽ��ϴ�.
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
