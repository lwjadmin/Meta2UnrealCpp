// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Texture2D.h"

#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"

AMyHUD::AMyHUD()
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> texture_sample(TEXT("Texture2D'/Game/MyContents/T_Crosshair.T_Crosshair'"));
    mTextureSample = texture_sample.Object;
}

void AMyHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    for (int i = 0; i < 20; i++)
    {
        ArrayList.Add(new FlyingText(this, GEngine->GameViewport->Viewport->GetSizeXY()));
    }
}

void AMyHUD::DrawHUD()
{

    const FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();

    for (auto arrayitem : ArrayList)
    {
        arrayitem->DrawText(GetWorld()->GetDeltaSeconds());
    }

    UTexture* texture = Cast<UTexture>(mTextureSample);


    int CrossHairSizeX = 200;
    int CrossHairSizeY = 200;

    const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));


    //텍스쳐의 사이즈를 가져올 때, GetSizeX, GetSizeY를 사용한다!!!
    //mTextureSample->GetSizeX();
    //mTextureSample->GetSizeY();

    DrawTexture(
        texture,
        (ViewportSize.X - (CrossHairSizeX * ViewportScale)) / 2, 
        (ViewportSize.Y - (CrossHairSizeY * ViewportScale)) / 2, 
        CrossHairSizeX * ViewportScale,
        CrossHairSizeY * ViewportScale,
        0, 0, 1, 1);
}