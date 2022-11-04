// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyActor2::AMyActor2() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> M_BasicShapeMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = RootMesh;
	RootMesh->SetMaterial(0,M_BasicShapeMaterial.Object);
	RootMesh->SetStaticMesh(SM_Sphere.Object);
	//TestEnum = ETestEnum::Unknown;
}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	
	switch (TestEnum)
	{
		case ETestEnum::Dance:
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Current State : ETestEnum::Dance"));
			break;
		}
		case ETestEnum::Rain:
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Current State : ETestEnum::Rain"));
			break;
		}
		//case ETestEnum::Song:
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Current State : ETestEnum::Song"));
		//	break;
		//}
	}
}

// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor2::CallInterface_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("MyActor2 Interface Called!"));
}