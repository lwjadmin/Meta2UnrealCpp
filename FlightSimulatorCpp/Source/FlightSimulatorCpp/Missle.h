// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missle.generated.h"

UCLASS()
class FLIGHTSIMULATORCPP_API AMissle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentHit
	(
		class UPrimitiveComponent* HitComponent, 
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		struct FVector NormalImpulse, 
		const struct FHitResult& Hit
	);

	UFUNCTION()
	void OnComponentBeginOverlap
	(
		class UPrimitiveComponent* OverlappedComponent, 
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const struct FHitResult& SweepResult
	);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* MissleBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* Movement;
	FTimerHandle SelfDestructTimer;
	void SelfDestruct();
	bool bIsDropBomb = false;
};
