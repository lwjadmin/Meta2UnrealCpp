// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


UCLASS()
class CTEST2_API AMyActor : public AActor, public ITestInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    void FStringTest();
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        UStaticMeshComponent* RootMesh;

    //C++ �� �������Ʈ������ Ȱ�밡���ϰ� ������ �������̽��̴�.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TestInterface")
    void CallInterface();
    virtual void CallInterface_Implementation() override;

};
