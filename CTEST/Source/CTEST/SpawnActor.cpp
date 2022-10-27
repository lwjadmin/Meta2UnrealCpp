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
	//타이머 설정, 0.3초마다 타이머 호출(무한루프)
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
	
	//BoxComponent에서 임의의 영역(X,Y,Z)을 반환하여 HitActor를 호출한다.
	FVector RandomLocation = FMath::RandPointInBox(SpawnBox->Bounds.GetBox());
	GetWorld()->SpawnActor<AHitActor>(RandomLocation, FRotator(0, 0, 0), spawnInfo);
}
