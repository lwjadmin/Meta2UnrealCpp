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

    //[1]Add�� ������Ʈ �������� �ν��Ͻ��� �迭�� ����(�Ǵ� �̵�)�մϴ�.
    strList.Add(TEXT("HELLO"));
    strList.Add(TEXT("WORLD"));

    FString strArr[] = { TEXT("NICE"), TEXT("TO"), TEXT("MEET"), TEXT("YOU") };
    //[2]Append�� �迭�� �����̳ʿ� ������ �� �ֽ��ϴ�.
    strList.Append(strArr, UE_ARRAY_COUNT(strArr));

    //AddUnique�� ���� �����̳ʰ� ������ ������Ʈ�� �������� ���� ��� �� ������Ʈ�� �߰��մϴ�.
    strList.AddUnique(TEXT("!"));
    strList.AddUnique(TEXT("!"));

    //Insert�� �����̳��� Ư�� ��ġ�� �� ������Ʈ�� �߰��մϴ�.
    strList.Insert(TEXT("BRAVE"), 1);

    //���յ� ���ڿ� ����Ʈ�� ����غ���
    FString Message = "";
    for (auto& str : strList)
    {
        Message += (" " + str);
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, Message);

    //String.Join
    FString Message2 = UKismetStringLibrary::JoinStringArray(strList);
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, Message2);

    //���ڿ� ����Ʈ�� Brave �����ϰ� �ϳ��� ����غ���
    for (int32 i = 0; i != strList.Num(); ++i)
    {
        if (strList[i].Compare(TEXT("BRAVE")) == 0)
        {
            continue;
        }
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, strList[i]);
    }

    //���ڿ� ����Ʈ�� �ϳ��� ����غ���
    for (FString str : strList)
    {
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, str);
    }

    TArray<int32> IntList;
    //�����̳� �ʱ�ȭ
    IntList.Init(10, 5); // IntArray = {10,10,10,10,10};

    //IntList �����̳� �ȿ� ����ִ� ��� ���� ���ؼ� ����غ���
    int32 sum = 0;
    for (auto ival : IntList)
    {
        sum += ival;
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, FString::FromInt(sum));

    //���ڿ��� ��ȯ �� "{10,10,10,10,10}"�� ���� �������� ����غ���
    FString strNumList = "";
    for (int32 i = 0; i != IntList.Num(); ++i)
    {
        //cout << i == 0 ? "{" : "" << IntList[i] << (i != IntList[i].Num()-1 ? ",":"}\n")
        strNumList.Append((i == 0 ? TEXT("{") : TEXT("")));
        strNumList.Append(FString::FromInt(IntList[i]));
        strNumList.Append((i != IntList.Num() - 1 ? TEXT(",") : TEXT("}")));
    }
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, strNumList);

    //�����̳��� �����̳� : ����, �����̳��� ��(Data) : Pointer�̴�. 
    TArray<TArray<FString>> strListList;
    strListList.Add(strList);
    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, strListList[0][0]);

    strListList.Add({ TEXT("0"),TEXT("1") });
    strListList[1].Add(TEXT("2"));

    GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, strListList[1][2]);


    //�⺻ ��� 
    UE_LOG(LogTemp, Warning, TEXT("Helloworld!"));

    //TEXT ����
    int32 IntVar = 5;
    float floatVar = 3.7f;
    FString stringVar = TEXT("TEST FSTRING");
    //FString�� ���, Class�̹Ƿ� Format ��� �� �����͸� �������.
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
    Test.Split(" ", nullptr, &TestRight); // Delimiter�� ����  Left / Right�θ� ���еȴ�... 

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

    //Blueprint : MyActor�� ��ӹ޾� TEST��� String ������Ƽ�� �����, ABC��� ������ �ʱ�ȭ�ߴ�. 
    //FindFProperty<FStrProperty>�� Ȱ���Ͽ� TEST ������Ƽ�� ������ �� �ִ�.
    //C++�ڵ�� �α� ���
    //FindFProperty<FStrProperty>
    FStrProperty* strProperty = FindFProperty<FStrProperty>(this->GetClass(), TEXT("TEST"));
    if (strProperty)
    {
        FString string = *strProperty->GetPropertyValue_InContainer(this);
        UE_LOG(LogTemp, Warning, TEXT("FStrProperty : %s"), *string);
    }

    /*-----------------------------------------------------------------------------
    CDO : Class Default Object = UObject
    1. �𸮾� ������ ������ �޴� Ŭ������ UObject Ŭ������ ��ӹ޴´�.
    2. ������ �� �𸮾� �����(UHT)���� UObject Ŭ������ ���õ� �ڵ�(��ġ C++�� C#ó�� ������ִ�)�� �����Ѵ�.
    3. ���� UObject�� UClass�� �����ǰ� �� ����, �� ���Ͱ� UClass �ν��Ͻ��� ��ӹ޴´�.
    4. ���忡 ��ġ�� Actor�� ����C++Ŭ������ ����� ���� Actor�϶� StaticClass(?)
    [TODO] AMyActor�� Enum���� ������ �ְ� StaticClass�� �����ؼ� �������� Get/Set�ϴ� ���� �׽�Ʈ�غ���!!
    -----------------------------------------------------------------------------*/
    if (this->GetClass() == AMyActor::StaticClass())
    {
        /*-------------------------------------------------------------------------
        ���� Ŭ�������� ȣ���� ��� (C++ ���͸� ���� ��ġ���� ��)
        -------------------------------------------------------------------------*/
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, TEXT("Same"));
    }
    else
    {
        /*-------------------------------------------------------------------------
        Ŭ���� �ν��Ͻ����� ȣ���� ��� (MyActor�� ��ӹ��� �������Ʈ��, MyActor�� ��ӹ��� �ٸ� C++ Ŭ������ ��ġ���� ��)
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

