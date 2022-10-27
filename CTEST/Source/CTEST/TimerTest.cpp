#include "TimerTest.h"
#include <Components/TextRenderComponent.h>

ATimerTest::ATimerTest()
{
    PrimaryActorTick.bCanEverTick = true;

    CountDownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountDownText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    CountDownText->SetWorldSize(150.0f);
    RootComponent = CountDownText;
    CountDown = 3;
}


void ATimerTest::BeginPlay()
{
    Super::BeginPlay();
    //타이머 설정
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerTest::AdvanceTimer, 1.0f, true);
    UpdateTimerDisplay();
}

// Called every frame
void ATimerTest::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATimerTest::UpdateTimerDisplay()
{
    FString msg = FString::Printf(TEXT("Countdown : %s"), *FString::FromInt(CountDown--));
    //FString msg = FString::Printf(TEXT("Countdown : %d"), CountDown--);
    //FString msg = FString::FromInt(CountDown);
    CountDownText->SetText(msg);
}

void ATimerTest::AdvanceTimer()
{
    --CountDown;
    UpdateTimerDisplay();
    if (CountDown < 1) 
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
        //GetWorldTimerManager().PauseTimer(TimerHandle);
        CountDownHasFinished();
    }
}

//void ATimerTest::CountDownHasFinished()
void ATimerTest::CountDownHasFinished_Implementation()
{
    /*--------------------------------------------------------------------------------------
        함수명에 "_Implementation()"을 붙일 경우 언리얼 헤더 툴(UHT)이 전처리 작업에서 가상함수 구현부를 작성해준다.
    --------------------------------------------------------------------------------------*/
    CountDownText->SetText("KABOOM!");
}


void ATimerTest::TimerCountDown()
{
    if (CountDown > 0)
    {
        FString str = FString::Printf(TEXT("Countdown : %s"), *FString::FromInt(CountDown--));
        CountDownText->SetText(str);
    }
    else
    {
        CountDownText->SetText(TEXT("KABOOM!"));
        GetWorldTimerManager().ClearTimer(TimerHandle);
        //GetWorldTimerManager().PauseTimer(TimerHandle);
    }
}