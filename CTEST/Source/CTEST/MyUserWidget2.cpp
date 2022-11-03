// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget2.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyUserWidget2::NativeConstruct()
{
    Super::Construct();

    UButton* btnStart = (UButton*)GetWidgetFromName(TEXT("btnStart"));
    UButton* btnExit = (UButton*)GetWidgetFromName(TEXT("btnExit"));

    if (btnStart)
    {
        btnStart->OnClicked.AddDynamic(this, &UMyUserWidget2::OnBtnStartClicked);
    }
    if (btnExit)
    {
        btnExit->OnClicked.AddDynamic(this, &UMyUserWidget2::OnBtnExitClicked);
    }
}

void UMyUserWidget2::OnBtnStartClicked()
{
    UGameplayStatics::OpenLevel(this, FName(TEXT("SecondMap")));
    FString CommandString = "r.SetRes";
    FString Resolution = "1920x1080";
    FString FullCommand = CommandString + " " + Resolution;
    GetWorld()->GetFirstPlayerController()->ConsoleCommand(FullCommand);

}

void UMyUserWidget2::OnBtnExitClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
