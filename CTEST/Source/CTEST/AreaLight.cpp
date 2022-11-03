// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaLight.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAreaLight::AAreaLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	static ConstructorHelpers::FObjectFinder<UMaterial>
		MatEmissive(TEXT("Material'/Game/Materials/M_Emmisive.M_Emmisive'"));

	RootBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComp"));

	//폰 오버랩 가능하게 설정
	RootBoxComp->SetGenerateOverlapEvents(true);
	//자신과의 충돌 방지
	RootBoxComp->SetCollisionObjectType(ECC_WorldDynamic);
	RootBoxComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	RootBoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AAreaLight::OnOverlapBegin);
	RootBoxComp->OnComponentEndOverlap.AddDynamic(this, &AAreaLight::OnOverlapEnd);
	SetRootComponent(RootBoxComp);

	CubeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMeshComp"));
	CubeMeshComp->SetGenerateOverlapEvents(false);
	CubeMeshComp->SetStaticMesh(CubeMesh.Object);
	CubeMeshComp->SetMaterial(0, MatEmissive.Object);
	CubeMeshComp->AttachTo(RootBoxComp);
	CubeMeshComp->SetRelativeScale3D(FVector(0.6, 0.6, 1));
	CubeMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CubeMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));
	PointLightComp->AttachTo(RootBoxComp);
	PointLightComp->SetVisibility(false);
}

// Called when the game starts or when spawned
void AAreaLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAreaLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAreaLight::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("ON!"));

	PointLightComp->SetVisibility(true);
}

void AAreaLight::OnOverlapEnd(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr))
		return;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("OFF!"));
	PointLightComp->SetVisibility(false);
}

UPointLightComponent* AAreaLight::GetPointLightInfo(bool& IsVisible, float& Intensity)
{
	IsVisible = PointLightComp->IsVisible();
	Intensity = DesiredIntensity;
	return PointLightComp;
}

float AAreaLight::GetDesiredIntensity()
{
	return DesiredIntensity;
}

