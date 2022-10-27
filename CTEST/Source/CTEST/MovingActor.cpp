#include "MovingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		m_mat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	mMesh->SetStaticMesh(m_Sphere.Object);
	mMesh->SetMaterial(0, m_mat.Object);
	RootComponent = mMesh;
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Pitch : Y, Yaw : X, Roll : Z
	//FVector(Yaw, Pitch, Roll);
	AddActorLocalOffset(FVector((1 * MoveSpeed * DeltaTime), 0, 0));

	if (bIsSmaller)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Smaller!!"));
		SetActorScale3D(GetActorScale3D() * 0.95f);

		if (GetActorScale3D().X < 0.05)
		{
			Destroy();
		}
	}
}

