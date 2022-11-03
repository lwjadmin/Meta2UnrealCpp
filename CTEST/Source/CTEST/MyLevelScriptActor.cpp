// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScriptActor.h"
#include "Blueprint/UserWidget.h"


void AMyLevelScriptActor::BeginPlay()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("AMyLevelScriptActor BeginPlay Called!"));
    switch (CurrentLevel)
    {
        case ELevel::Unknown:
        {
            CurrentLevel = ELevel::MenuLevel;
        }
        case ELevel::MenuLevel:
        {
            UBlueprint* obj = LoadObject<UBlueprint>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/UMG_MainMenu.UMG_MainMenu'"));
            UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), *obj->GeneratedClass);
            ui->AddToViewport();
            break;
        }
        case ELevel::GameLevel:
        {
            UBlueprint* obj = LoadObject<UBlueprint>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/test.test'"));
            UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), *obj->GeneratedClass);
            ui->AddToViewport();
            break;
        }
    }
}