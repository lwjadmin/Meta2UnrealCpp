// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

/*------------------------------------------------------------------------

열거형(Enum)

열거형은 기본적으로 저렴한 비용의 데이터 유형을 사용하여,
사람이 읽을 수 있는 긴 이름으로 일련의 관련 유형을 정의할 수 있는 기능을 제공합니다.
열거형 업데이트 후 디테일에 목록이 갱신될 것이라 예상했으나, 에디터를 껐다 켜야 새롭게 추가된 항목이 갱신된다!!

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
    //구조체 안에서 변수를 사용할 때
    //UPROPERTY가 아닌 구조체 변수는 복제되지 않습니다.

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

    //C++ 및 블루프린트에서도 활용가능하게 변경한 인터페이스이다.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TestInterface")
        void CallInterface();
    virtual void CallInterface_Implementation() override;

};
