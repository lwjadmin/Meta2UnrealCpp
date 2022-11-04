// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirePartcleActor.generated.h"



UCLASS()
class CTEST2_API AFirePartcleActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFirePartcleActor();

    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    UFUNCTION()
    void OnMeshCreation();
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        class USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        class UParticleSystem* FX_Fire;

    //오브젝트 레퍼런스 : 생성된 객체에 대한 주소를 가리킨다. 
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidget")
        class UUserWidget* widget;

    /*---------------------------------------------------------------------------------
    TSubclassOf<T> 클래스 형태의 직접 레퍼런싱이다. 자동 로딩이 데이터형은 Type안정성을 위해 사용하는 경우가 많다.
    즉, 값으로 들어오는 클래스 정보는 T를 상속한 Class다 라는 의미를 명확히 할 때, 사용되는 데이터형이다.

    이것도 기본적으로는 내부에 UClass* 데이터를 가지고 있다.
    호환되는 TSubClassOf 유형을 서로에게 할당하는 연산은 RunTime에 Check하고,
    서로 호환되지 않는 TSubClassOf 유형(공통 부모조차 없는 전혀다른 클래스)는 Compile시간에 체크한다.
    왜냐하면 호환되는 유형은 null값 등이 사용될 수 있지만, 서로 호환되지 않는 유형은 Crash를 유발할 수 있기 때문!
    ---------------------------------------------------------------------------------*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidget")
        TSubclassOf<UUserWidget> Widget_Class;

    /*---------------------------------------------------------------------------------
    약참조 - 동기/비동기 : Lazy Loading
    TSoftClassPtr<T> 간접 레퍼런싱 수동 로딩
    말 그대로 Class의 Soft Pointer라는 뜻으로, 해당 값이 가리키는 데이터는 직접 지정한 template형의 것이다.
    그리고, 그 데이터는 UClass로, UE4 엔진이 살행될 때 처음 생성되어 보관되어지는 Unreal Class Metadata일 것이다.
    만약, 한번도 생성되지 못한 것이라면, LoadSynchronous()를 통해 해당 CDO(Class Default Object)를 생성해줄 수 있다.
    Get()은 Load된 UClass를 반환한다. CDO를 반환하는 것이다.
    해당 데이터형을 사용하려면, Get()이나 LoadSynchronous()를 잘 활용해야 할 것이다.
    ---------------------------------------------------------------------------------*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidget")
        TSoftClassPtr<UUserWidget> Widget_SoftClass;

    UFUNCTION()
        void OnAsset();



    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
        UStaticMesh* BaseMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
        TSoftObjectPtr<UStaticMesh> SoftMesh;
};
