// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTEST2GameModeBase.h"

#include "MyActor.h"
#include "MyActor2.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


/*---------------------------------------------------------------
    1. ���Ӹ�庣�̽��� BeginPlay�� �����.
    2. ��� ���͸� ã�� �������̽��� ������ ���, �������̽� �޽����� ȣ������.
---------------------------------------------------------------*/
void ACTEST2GameModeBase::BeginPlay()
{

    //CASE 1 : Iterator�� ����Ͽ� ��� ���Ϳ� ���ؼ� �������̽� ĳ���� ������ ȣ��
    //for (TActorIterator<AActor> actor(GWorld); actor; ++actor)
    //{
    //    ITestInterface* test = Cast<ITestInterface>(*actor);
    //    if (test)
    //    {
    //        test->Execute_CallInterface(*actor);
    //    }
    //}
    
    //CASE 2 : UGameplayStatics�� ����Ͽ� ��� ���Ϳ� ���ؼ� �������̽� ĳ���� ������ ȣ��
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
