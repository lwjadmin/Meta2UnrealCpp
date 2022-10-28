// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaLight.generated.h"

UCLASS()
class CTEST_API AAreaLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
        void OnOverlapBegin
        (
            class UPrimitiveComponent* OverlappedComponent,
            AActor* OtherActor,
            class UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bFromSweep,
            const FHitResult& SweepResult
        );

    UFUNCTION()
        void OnOverlapEnd
        (
            class UPrimitiveComponent* HitComp,
            AActor* OtherActor,
            class UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex
        );

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    class UBoxComponent* RootBoxComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    class UPointLightComponent* PointLightComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    class UStaticMeshComponent* CubeMeshComp;
};
