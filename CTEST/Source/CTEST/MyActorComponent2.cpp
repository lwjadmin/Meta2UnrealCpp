// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent2.h"

// Sets default values for this component's properties
UMyActorComponent2::UMyActorComponent2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (FollowTarget)
	{
		//현재에서 대상으로 벡터를 보간(재조정)한다. 대상까지의 거리에 따라 조정되므로 시작 속도가 빠르고 쉽게 빠져나간다.
		FVector move = FMath::VInterpTo(GetOwner()->GetActorLocation(), FollowTarget->GetActorLocation(), DeltaTime, FollowSpeed);
		GetOwner()->SetActorLocation(move, true);
	}
}

void UMyActorComponent2::SetFollowTarget(AActor* target, float speed)
{
	FollowTarget = target;
	FollowSpeed = speed;
}

