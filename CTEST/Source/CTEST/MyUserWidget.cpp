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
    //������Ʈ �Ӽ��� : Anim(UMG Animation)�� ã�´�. 
    
    
    FObjectProperty* BlueprintClassProperty = FindFProperty<FObjectProperty>(this->GetClass(), TEXT("Anim"));
    //FindField ���� ����, UFunction �Ǵ� UEnum�� ã������ FindFProperty �Ǵ� FindUField�� ����ϴ� ���� ������.
    //UObjectProperty* objProperty = FindField<UObjectProperty>(this->GetClass(), TEXT("Anim"));
    if (BlueprintClassProperty)
    {
        //UWidgetAnimation* anim = Cast<UWidgetAnimation>(objProperty->GetPropertyValue_InContainer(this));
        UWidgetAnimation* anim = Cast<UWidgetAnimation>(BlueprintClassProperty->GetObjectPropertyValue_InContainer(this));
        
        //PlayAnimation(Animation, StartPosition, repeatCount (0 : Loop, 1 : Once...))
        PlayAnimation(anim, 0, 1);

        //�ִϸ��̼��� ������ �� �̺�Ʈ�� �޾ƿ��� ���
        //������ �ִϸ��̼� ���� ���ε��� �ɷ������� �������ش�.
        UnbindAllFromAnimationFinished(anim);
        //�ִϸ��̼ǿ� "�ִϸ��̼� ���� �̺�Ʈ ��������Ʈ"�� ���ε��Ѵ�.
        FWidgetAnimationDynamicEvent EndDelegate;
        EndDelegate.BindDynamic(this, &UMyUserWidget::OnEndAnim);
        BindToAnimationFinished(anim, EndDelegate);
    }
}

void UMyUserWidget::OnEndAnim()
{
    //�ִϸ��̼��� ����Ǹ� OnEndAnim()�� ȣ���Ѵ�!
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Animation Finished!"));
}