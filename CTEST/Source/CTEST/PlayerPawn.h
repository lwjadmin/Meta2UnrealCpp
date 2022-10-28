// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "PlayerPawn.generated.h"


/*---------------------------------------------------------------
DefaultPawn�� ���������� ���� ������, ī�޶� �ڵ����� ��ġ�Ǿ� 
���콺XY�� �̵��� ī�޶� ȸ���Ѵ�.
---------------------------------------------------------------*/
UCLASS()
class CTEST_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void MouseButtonClick();


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	//class UStaticMeshComponent* RootMesh;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	//class USpringArmComponent* CameraArm;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	//class UCameraComponent* FollowCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float MoveSpeed = 1000.0f;
};
