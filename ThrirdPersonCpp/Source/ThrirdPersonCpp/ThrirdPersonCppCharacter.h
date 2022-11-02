// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThrirdPersonCppCharacter.generated.h"

UCLASS(config=Game)
class AThrirdPersonCppCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AThrirdPersonCppCharacter();
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UCameraComponent* FollowCamera;
};

