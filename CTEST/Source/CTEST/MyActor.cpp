#include "MyActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"

//���ο� ī�װ��� ���� �� ����ϴ� ��ũ���̴�. 
DEFINE_LOG_CATEGORY(LogMyActor);

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EngineDefaultSphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> mat(TEXT("Material'/Game/Materials/M_Color.M_Color'"));
	if (mat.Succeeded())
	{
		MyMat = mat.Object;
	}
	RootComponent = StaticMesh;
	StaticMesh->SetStaticMesh(EngineDefaultSphereMesh.Object);
	
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//3�ʿ� 1�� TimerTestHandle ���� 
	UMaterialInstanceDynamic* MyMatInst = UMaterialInstanceDynamic::Create(MyMat, StaticMesh);
	MyMatInst->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(1, 0, 0, 0));
	StaticMesh->SetMaterial(0, MyMatInst);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::OnTimer, 3.0f, false/*true : Looping*/);
}

void AMyActor::OnTimer()
{
	//����Ʈ Print
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

	//���带 �������� ��ġ�� ��Ÿ���� �߰��Ѵ�.
	//AddActorWorldOffset(FVector(0, 0, 1));
	//����(����)�� �������� ��ġ�� ��Ÿ���� �߰��Ѵ�.
	AddActorLocalOffset(FVector(0, 0, 1));
}

void AMyActor::TestFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("TestFunction Called!"));
}