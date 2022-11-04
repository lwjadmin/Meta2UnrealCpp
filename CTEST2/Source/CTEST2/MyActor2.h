// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

/*------------------------------------------------------------------------

������(Enum)

�������� �⺻������ ������ ����� ������ ������ ����Ͽ�,
����� ���� �� �ִ� �� �̸����� �Ϸ��� ���� ������ ������ �� �ִ� ����� �����մϴ�.
������ ������Ʈ �� �����Ͽ� ����� ���ŵ� ���̶� ����������, �����͸� ���� �Ѿ� ���Ӱ� �߰��� �׸��� ���ŵȴ�!!

------------------------------------------------------------------------*/
UENUM(BlueprintType)
enum class ETestEnum : uint8 //uint8 : unsigned char [0~255]
{
    Unknown UMETA(DisplayName = "Unknown"),
    Dance   UMETA(DisplayName = "Dance"),
    Rain    UMETA(DisplayName = "Rain"),
    Song    UMETA(DisplayName = "Song"),
    A       UMETA(DisplayName = "A"),
    B       UMETA(DisplayName = "B"),
    C       UMETA(DisplayName = "C")
};

USTRUCT(BlueprintType)
struct FTestStruct
{
    GENERATED_BODY()
public:
    //����ü �ȿ��� ������ ����� ��
    //UPROPERTY�� �ƴ� ����ü ������ �������� �ʽ��ϴ�.

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FTestStruct")
        int32 NumPetals;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FTestStruct")
        FLinearColor Color;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FTestStruct")
        FVector Scale3D;
};

UCLASS()
class CTEST2_API AMyActor2 : public AActor, public ITestInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActor2();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        UStaticMeshComponent* RootMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
        ETestEnum TestEnum;

    //C++ �� �������Ʈ������ Ȱ�밡���ϰ� ������ �������̽��̴�.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TestInterface")
        void CallInterface();
    virtual void CallInterface_Implementation() override;

};
