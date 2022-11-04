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

    //������Ʈ ���۷��� : ������ ��ü�� ���� �ּҸ� ����Ų��. 
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidget")
        class UUserWidget* widget;

    /*---------------------------------------------------------------------------------
    TSubclassOf<T> Ŭ���� ������ ���� ���۷����̴�. �ڵ� �ε��� ���������� Type�������� ���� ����ϴ� ��찡 ����.
    ��, ������ ������ Ŭ���� ������ T�� ����� Class�� ��� �ǹ̸� ��Ȯ�� �� ��, ���Ǵ� ���������̴�.

    �̰͵� �⺻�����δ� ���ο� UClass* �����͸� ������ �ִ�.
    ȣȯ�Ǵ� TSubClassOf ������ ���ο��� �Ҵ��ϴ� ������ RunTime�� Check�ϰ�,
    ���� ȣȯ���� �ʴ� TSubClassOf ����(���� �θ����� ���� �����ٸ� Ŭ����)�� Compile�ð��� üũ�Ѵ�.
    �ֳ��ϸ� ȣȯ�Ǵ� ������ null�� ���� ���� �� ������, ���� ȣȯ���� �ʴ� ������ Crash�� ������ �� �ֱ� ����!
    ---------------------------------------------------------------------------------*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidget")
        TSubclassOf<UUserWidget> Widget_Class;

    /*---------------------------------------------------------------------------------
    ������ - ����/�񵿱� : Lazy Loading
    TSoftClassPtr<T> ���� ���۷��� ���� �ε�
    �� �״�� Class�� Soft Pointer��� ������, �ش� ���� ����Ű�� �����ʹ� ���� ������ template���� ���̴�.
    �׸���, �� �����ʹ� UClass��, UE4 ������ ����� �� ó�� �����Ǿ� �����Ǿ����� Unreal Class Metadata�� ���̴�.
    ����, �ѹ��� �������� ���� ���̶��, LoadSynchronous()�� ���� �ش� CDO(Class Default Object)�� �������� �� �ִ�.
    Get()�� Load�� UClass�� ��ȯ�Ѵ�. CDO�� ��ȯ�ϴ� ���̴�.
    �ش� ���������� ����Ϸ���, Get()�̳� LoadSynchronous()�� �� Ȱ���ؾ� �� ���̴�.
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
