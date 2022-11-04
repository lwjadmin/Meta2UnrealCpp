// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> M_BasicShapeMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

    RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
    RootComponent = RootMesh;
    RootMesh->SetMaterial(0, M_BasicShapeMaterial.Object);
    RootMesh->SetStaticMesh(SM_Sphere.Object);

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    //FStringTest();

    ITestInterface* TestInterface = Cast<ITestInterface>(this);
    if (TestInterface)
    {
        TestInterface->Execute_CallInterface(this);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("MyActor Not Implements ITestInterface!!"));
    }
}

void AMyActor::FStringTest()
{
    TArray<FString> strList;

    //[1]Add는 엘리먼트 유형으로 인스턴스를 배열에 복사(또는 이동)합니다.
    strList.Add(TEXT("HELLO"));
    strList.Add(TEXT("WORLD"));

    FString strArr[] = { TEXT("NICE"), TEXT("TO"), TEXT("MEET"), TEXT("YOU") };
    //[2]Append는 배열을 컨테이너에 복사할 수 있습니다.
    strList.Append(strArr, UE_ARRAY_COUNT(strArr));

    //AddUnique는 기존 컨테이너가 동일한 엘리먼트가 존재하지 않을 경우 새 엘리먼트만 추가합니다.
    strList.AddUnique(TEXT("!"));
    strList.AddUnique(TEXT("!"));

    //Insert는 컨테이너의 특정 위치에 새 엘리먼트를 추가합니다.
    strList.Insert(TEXT("BRAVE"), 1);

    //결합된 문자열 리스트를 출력해보기
    FString Message = "";
    for (auto& str : strList)
    {
        Message += (" " + str);
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, Message);

    //String.Join
    FString Message2 = UKismetStringLibrary::JoinStringArray(strList);
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, Message2);

    //문자열 리스트를 Brave 제외하고 하나씩 출력해보기
    for (int32 i = 0; i != strList.Num(); ++i)
    {
        if (strList[i].Compare(TEXT("BRAVE")) == 0)
        {
            continue;
        }
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, strList[i]);
    }

    //문자열 리스트를 하나씩 출력해보기
    for (FString str : strList)
    {
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, str);
    }

    TArray<int32> IntList;
    //컨테이너 초기화
    IntList.Init(10, 5); // IntArray = {10,10,10,10,10};

    //IntList 컨테이너 안에 들어있는 모든 값을 더해서 출력해보기
    int32 sum = 0;
    for (auto ival : IntList)
    {
        sum += ival;
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, FString::FromInt(sum));

    //문자열로 변환 후 "{10,10,10,10,10}"과 같은 형식으로 출력해보기
    FString strNumList = "";
    for (int32 i = 0; i != IntList.Num(); ++i)
    {
        //cout << i == 0 ? "{" : "" << IntList[i] << (i != IntList[i].Num()-1 ? ",":"}\n")
        strNumList.Append((i == 0 ? TEXT("{") : TEXT("")));
        strNumList.Append(FString::FromInt(IntList[i]));
        strNumList.Append((i != IntList.Num() - 1 ? TEXT(",") : TEXT("}")));
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, strNumList);

    //컨테이너의 컨테이너 : 가능, 컨테이너의 값(Data) : Pointer이다. 
    TArray<TArray<FString>> strListList;
    strListList.Add(strList);
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, strListList[0][0]);

    strListList.Add({ TEXT("0"),TEXT("1") });
    strListList[1].Add(TEXT("2"));

    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, strListList[1][2]);


    //기본 사용 
    UE_LOG(LogTemp, Warning, TEXT("Helloworld!"));

    //TEXT 조합
    int32 IntVar = 5;
    float floatVar = 3.7f;
    FString stringVar = TEXT("TEST FSTRING");
    //FString의 경우, Class이므로 Format 사용 시 포인터를 사용하자.
    UE_LOG(LogTemp, Warning, TEXT("Some Warning Message : %d %f %s"), IntVar, floatVar, *stringVar);

    //OLD C Style String Formatting...
    FString name = TEXT("TIM");
    int32 mana = 450;
    FString string1 = FString::Printf(TEXT("Name = %s, Mana = %d"), *name, mana);
    UE_LOG(LogTemp, Warning, TEXT("Your String1 :  %s"), *string1);

    //C# Style String Formatting....
    TArray<FStringFormatArg> args;
    args.Add(FStringFormatArg(name));
    args.Add(FStringFormatArg(mana));
    FString string2 = FString::Format(TEXT("Name = {0}, Mana = {1}"), args);
    UE_LOG(LogTemp, Warning, TEXT("Your String2 :  %s"), *string2);

    FString Test = TEXT("1234 TEST");
    FString TestRight;
    Test.Split(" ", nullptr, &TestRight); // Delimiter에 따라  Left / Right로만 구분된다... 

    //FString Equal Check 
    if (TestRight.Equals(TEXT("TEST")))
    {
        UE_LOG(LogTemp, Warning, TEXT("EQUAL"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NOTEQUAL"));
    }

    //FString Contains Check
    if (Test.Find(TEXT("TEST")))
    {
        UE_LOG(LogTemp, Warning, TEXT("Variable Test Contains Word : TEST"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Variable Test Not Contains Word : TEST"));
    }

    //Blueprint : MyActor를 상속받아 TEST라는 String 프로퍼티를 만들고, ABC라는 값으로 초기화했다. 
    //FindFProperty<FStrProperty>를 활용하여 TEST 프로퍼티에 접근할 수 있다.
    //C++코드로 로그 출력
    //FindFProperty<FStrProperty>
    FStrProperty* strProperty = FindFProperty<FStrProperty>(this->GetClass(), TEXT("TEST"));
    if (strProperty)
    {
        FString string = *strProperty->GetPropertyValue_InContainer(this);
        UE_LOG(LogTemp, Warning, TEXT("FStrProperty : %s"), *string);
    }

    /*-----------------------------------------------------------------------------
    CDO : Class Default Object = UObject
    1. 언리얼 엔진의 관리를 받는 클래스는 UObject 클래스를 상속받는다.
    2. 컴파일 시 언리얼 헤더툴(UHT)에서 UObject 클래스와 관련된 코드(마치 C++을 C#처럼 만들어주는)를 생성한다.
    3. 개별 UObject의 UClass가 생성되고 난 다음, 각 액터가 UClass 인스턴스를 상속받는다.
    4. 월드에 배치된 Actor가 원본C++클래스를 끌어다 만든 Actor일때 StaticClass(?)
    [TODO] AMyActor에 Enum등의 변수를 넣고 StaticClass로 접근해서 변수값을 Get/Set하는 것을 테스트해보자!!
    -----------------------------------------------------------------------------*/
    if (this->GetClass() == AMyActor::StaticClass())
    {
        /*-------------------------------------------------------------------------
        원본 클래스에서 호출할 경우 (C++ 액터를 직접 배치했을 때)
        -------------------------------------------------------------------------*/
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, TEXT("Same"));
    }
    else
    {
        /*-------------------------------------------------------------------------
        클래스 인스턴스에서 호출할 경우 (MyActor를 상속받은 블루프린트나, MyActor를 상속받은 다른 C++ 클래스를 배치했을 때)
        -------------------------------------------------------------------------*/
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, TEXT("No"));
    }
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AMyActor::CallInterface_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("MyActor Interface Called!"));
}

