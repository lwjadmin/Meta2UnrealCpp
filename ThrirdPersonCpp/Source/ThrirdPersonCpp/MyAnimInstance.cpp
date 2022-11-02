// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* MyPawn = TryGetPawnOwner();
    if (IsValid(MyPawn))
    {
        bIsInAir = MyPawn->GetMovementComponent()->IsFalling();
        Speed = MyPawn->GetVelocity().Size();
    }
}