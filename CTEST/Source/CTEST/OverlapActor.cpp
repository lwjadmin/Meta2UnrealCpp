// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"


// Sets default values
AOverlapActor::AOverlapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMCube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> BasicMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	UStaticMeshComponent* BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));

	RootComponent = SceneRoot;
	BoxMesh->SetupAttachment(SceneRoot);
	BoxMesh->SetStaticMesh(SMCube.Object);
	BoxMesh->SetMaterial(0,BasicMaterial.Object);
	BoxMesh->SetSimulatePhysics(true);
	//BoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverlapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverlapActor::ActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString msg = FString::Printf(TEXT("Overlapped Actor : %s"), *OtherActor->GetActorLabel());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, msg);
}

