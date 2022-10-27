#include "CTESTGameModeBase.h"
#include "MyPawn.h"
#include "MyActor.h"

ACTESTGameModeBase::ACTESTGameModeBase()
{
    //CDO�� Ŭ���� �⺻ ��ü�� �ҷ��´�.
    DefaultPawnClass = AMyPawn::StaticClass();
}

void ACTESTGameModeBase::BeginPlay()
{
    /*---------------------------------------------------------------------------
        AMyActor* ActorPtr = NewObject<AMyActor>(this, TEXT("TESTUObject"));
        UObject* ObjPtr = ActorPtr;
        UClass* MyActorClass = AMyActor::StaticClass(); //AMyActor;
        UClass* ObjectClass = UObject::StaticClass(); //UObject;
        UClass* ActorPtrClass = ActorPtr->GetClass(); //AMyActor;
        UClass* ObjPtrClass = ObjPtr->GetClass(); //AMyActor;

        //UClass�� �������� ���� : �ٸ������� Ŭ������ �ν��Ͻ��� ���� UClass�� ����.
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *MyActorClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjectClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ActorPtrClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjPtrClass->GetName());


        �� StaticClass/GetClass ��� : 
        �𸮾� CDO�� ����ϱ� ���� ��. �̰��� ����ϸ� �ð��� ���ҽ��� �����Ѵ�.
        StaticClass�� ������ Ÿ�ӿ��� UClass Ÿ���� ������ ������ ���̸�,
        GetClass�� ��Ÿ�ӿ��� ���� ��ü�� Ŭ������ ��ȸ�� �� ����Ѵ�.
        StaticClass�� ������ Ÿ�ӿ� �̹� ������ ���̴�. ������ �����Ͱ� ó���ϴ� ���� ��ü��
        Ÿ���� ��Ÿ�ӿ��� �޶��� �� �����Ƿ�, ���� ��ü�� Ŭ������ �����ϴ� GetClass�� ���ϰ���
        StaticClass�� ���ϰ��� �ٸ� �� �ִ�.
    ---------------------------------------------------------------------------*/

}