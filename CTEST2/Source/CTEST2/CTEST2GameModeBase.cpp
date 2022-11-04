// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTEST2GameModeBase.h"

#include "MyActor.h"
#include "MyActor2.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


/*---------------------------------------------------------------
    1. 게임모드베이스에 BeginPlay를 만든다.
    2. 모든 액터를 찾아 인터페이스를 포함할 경우, 인터페이스 메시지를 호출하자.
---------------------------------------------------------------*/
void ACTEST2GameModeBase::BeginPlay()
{

    //CASE 1 : Iterator를 사용하여 모든 액터에 대해서 인터페이스 캐스팅 성공시 호출
    //for (TActorIterator<AActor> actor(GWorld); actor; ++actor)
    //{
    //    ITestInterface* test = Cast<ITestInterface>(*actor);
    //    if (test)
    //    {
    //        test->Execute_CallInterface(*actor);
    //    }
    //}
    
    //CASE 2 : UGameplayStatics를 사용하여 모든 액터에 대해서 인터페이스 캐스팅 성공시 호출
    TArray<AActor*> ActorList;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorList);
    for (int i = 0; i < ActorList.Num(); i++)
    {
        ITestInterface* test = Cast<ITestInterface>(ActorList[i]);
        if (test)
        {
            test->Execute_CallInterface(ActorList[i]);
        }
    }

}
