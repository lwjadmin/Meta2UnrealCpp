#include "CTESTGameModeBase.h"
#include "MyPawn.h"
#include "MyActor.h"

ACTESTGameModeBase::ACTESTGameModeBase()
{
    //CDO로 클래스 기본 객체를 불러온다.
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

        //UClass를 가져오는 이유 : 다른곳에서 클래스의 인스턴스를 쓸때 UClass를 쓴다.
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *MyActorClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjectClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ActorPtrClass->GetName());
        UE_LOG(LogClass, Error, TEXT("Name : %s"), *ObjPtrClass->GetName());


        ※ StaticClass/GetClass 요약 : 
        언리얼 CDO를 사용하기 위한 것. 이것을 사용하면 시간과 리소스를 절약한다.
        StaticClass는 컴파일 타임에서 UClass 타입의 정보를 얻어오는 것이며,
        GetClass는 런타임에서 실제 객체의 클래스를 조회할 때 사용한다.
        StaticClass는 컴파일 타임에 이미 정해진 것이다. 하지만 포인터가 처리하는 실제 객체의
        타입은 런타임에서 달라질 수 있으므로, 실제 객체의 클래스를 리턴하는 GetClass의 리턴값은
        StaticClass의 리턴값과 다를 수 있다.
    ---------------------------------------------------------------------------*/

}