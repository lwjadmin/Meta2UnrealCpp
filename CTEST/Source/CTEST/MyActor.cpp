#include "MyActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"

//새로운 카테고리를 만들 때 사용하는 매크로이다. 
DEFINE_LOG_CATEGORY(LogMyActor);

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineDefaultSphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MyMat(TEXT("Material'/Game/Materials/M_Color.M_Color'"));
	
	RootComponent = StaticMesh;
	//SetRootComponent(StaticMesh);

	StaticMesh->SetStaticMesh(EngineDefaultSphereMesh.Object);
	UMaterialInstanceDynamic* MyMatInst = UMaterialInstanceDynamic::Create(MyMat.Object, StaticMesh);
	MyMatInst->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(1, 0, 0, 0));
	StaticMesh->SetMaterial(0, MyMatInst);
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//3초에 1번 TimerTestHandle 실행 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::OnTimer, 3.0f, false/*true : Looping*/);
}

void AMyActor::OnTimer()
{
	//뷰포트 Print
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("OnTimer Called"));

	//Spawn Emitter At Location
	UParticleSystem* FxExplosion = LoadObject<UParticleSystem>(nullptr,
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FxExplosion, this->GetActorTransform());
	this->Destroy();
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//월드를 기준으로 위치에 델타값을 추가한다.
	//AddActorWorldOffset(FVector(0, 0, 1));
	//로컬(액터)을 기준으로 위치에 델타값을 추가한다.
	AddActorLocalOffset(FVector(0, 0, 1));
}

