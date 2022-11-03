// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

void UMyUserWidget::NativeConstruct()
{
    Super::Construct();

    UButton* TestButton = (UButton*)GetWidgetFromName(TEXT("btnUMG"));
    if (TestButton)
    {
        TestButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnClicked);
    }
    
}
void UMyUserWidget::OnClicked()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("UMG_Clicked_Test!"));
    //오브젝트 속성명 : Anim(UMG Animation)을 찾는다. 
    
    
    FObjectProperty* BlueprintClassProperty = FindFProperty<FObjectProperty>(this->GetClass(), TEXT("Anim"));
    //FindField 지원 종료, UFunction 또는 UEnum을 찾으려면 FindFProperty 또는 FindUField를 사용하는 것을 권장함.
    //UObjectProperty* objProperty = FindField<UObjectProperty>(this->GetClass(), TEXT("Anim"));
    if (BlueprintClassProperty)
    {
        //UWidgetAnimation* anim = Cast<UWidgetAnimation>(objProperty->GetPropertyValue_InContainer(this));
        UWidgetAnimation* anim = Cast<UWidgetAnimation>(BlueprintClassProperty->GetObjectPropertyValue_InContainer(this));
        
        //PlayAnimation(Animation, StartPosition, repeatCount (0 : Loop, 1 : Once...))
        PlayAnimation(anim, 0, 1);

        //애니메이션이 끝났을 때 이벤트를 받아오는 방법
        //기존에 애니메이션 종료 바인딩이 걸려있으면 해제해준다.
        UnbindAllFromAnimationFinished(anim);
        //애니메이션에 "애니메이션 종료 이벤트 델리게이트"를 바인딩한다.
        FWidgetAnimationDynamicEvent EndDelegate;
        EndDelegate.BindDynamic(this, &UMyUserWidget::OnEndAnim);
        BindToAnimationFinished(anim, EndDelegate);
    }
}

void UMyUserWidget::OnEndAnim()
{
    //애니메이션이 종료되면 OnEndAnim()을 호출한다!
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Animation Finished!"));
}