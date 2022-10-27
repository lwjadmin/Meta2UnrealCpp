// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnActor.h"
#include "Components/BoxComponent.h"

#include "HitActor.h"

ASpawnActor::ASpawnActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SetRootComponent(SpawnBox);
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	//Ÿ�̸� ����, 0.3�ʸ��� Ÿ�̸� ȣ��(���ѷ���)
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnActor::Spawn, 0.3f, true);
}

void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnActor::Spawn()
{
	FActorSpawnParameters spawnInfo = FActorSpawnParameters();
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	//BoxComponent���� ������ ����(X,Y,Z)�� ��ȯ�Ͽ� HitActor�� ȣ���Ѵ�.
	FVector RandomLocation = FMath::RandPointInBox(SpawnBox->Bounds.GetBox());
	GetWorld()->SpawnActor<AHitActor>(RandomLocation, FRotator(0, 0, 0), spawnInfo);
}
