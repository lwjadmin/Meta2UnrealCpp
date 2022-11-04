// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        m_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
        m_mat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootMesh->SetStaticMesh(m_Sphere.Object);
	RootMesh->SetMaterial(0, m_mat.Object);
	RootComponent = RootMesh;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	PrintLogA(TEXT("HELLO UNREAL CPP!!"));
	UE_LOG(LogTemp, Warning, TEXT("HELLO UNREAL DEBUG LOG!!"));
}

void AMyActor::PrintLogA(FString msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, msg);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

