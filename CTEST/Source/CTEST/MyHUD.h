// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class FlyingText;

UCLASS()
class CTEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	//DrawHUD : 매 드로우콜 (매 틱)마다 호출 (Tick과 유사함!!)
	virtual void DrawHUD() override;
    virtual void PostInitializeComponents() override;
    TArray<FlyingText*> ArrayList;

    class UTexture2D* mTextureSample;

    AMyHUD();
};

class FlyingText
{
public:
    AMyHUD* HUD;
    FVector2D ViewportSize;
    int PosX = 0;
    int PosY = 0;
    float MoveSpeed = 0.0f;
    bool bRightChecked = false;
    bool bBottomChecked = false;
    TArray<FLinearColor> ColorPack;
    FLinearColor Color;

    FlyingText(AMyHUD* InHUD, FVector2D InViewportSize)
    {
        HUD = InHUD;
        ViewportSize = InViewportSize;
        PosX = (int)FMath::RandRange(150.0f, ViewportSize.X - 150.0f);
        PosY = (int)FMath::RandRange(150.0f, ViewportSize.Y - 150.0f);
        MoveSpeed = FMath::RandRange(100.0f, 300.0f);

        //ColorPack.Add(FLinearColor::Red);
        //ColorPack.Add(FLinearColor::Green);
        //ColorPack.Add(FLinearColor::Blue);
        //ColorPack.Add(FLinearColor::Green);
        //ColorPack.Add(FLinearColor::Yellow);

        //Color = ColorPack[(int)FMath::RandRange(0, ColorPack.Num())];
        Color = FLinearColor::Blue; 
    }

    void DrawText(float DeltaSeconds)
    {
        if (!bRightChecked)
        {
            PosX = PosX + (DeltaSeconds * MoveSpeed);
            if (PosX > ViewportSize.X)
            {
                bRightChecked = true;
            }
        }
        else
        {
            PosX = PosX - (DeltaSeconds * MoveSpeed);
            if (PosX < 0)
            {
                bRightChecked = false;
            }
        }

        if (!bBottomChecked)
        {
            PosY = PosY + (DeltaSeconds * MoveSpeed);
            if (PosY > ViewportSize.Y)
            {
                bBottomChecked = true;
            }
        }
        else
        {
            PosY = PosY - (DeltaSeconds * MoveSpeed);
            if (PosY < 0)
            {
                bBottomChecked = false;
            }
        }
        HUD->DrawText(TEXT("TEXT"), Color, PosX, PosY, GEngine->GetLargeFont());
    }
};