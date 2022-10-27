
#include "HitActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"
#include "MyPawn.h"


AHitActor::AHitActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial>
		m_colormat(TEXT("Material'/Game/Materials/M_Color.M_Color'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UStaticMeshComponent* mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComponent"));
	UMaterialInstanceDynamic* mi_colormat = UMaterialInstanceDynamic::Create(m_colormat.Object, mMesh);

	RootComponent = mMesh;
	mMesh->SetStaticMesh(m_Sphere.Object);
	float colorR = FMath::FRandRange(0, 1);
	float colorG = FMath::FRandRange(0, 1);
	float colorB = FMath::FRandRange(0, 1);

	mi_colormat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(colorR, colorG, colorB));
	mMesh->SetMaterial(0, mi_colormat);

	//���� ����
	mMesh->SetSimulatePhysics(true);
	//�ùķ��̼��� Hit Event�� �����ϵ��� ����(Simulation Generates Hit Events [Check : true / Uncheck : false]
	mMesh->SetNotifyRigidBodyCollision(true);

	//�Լ� ���ε�(OnActorHit)
	//this->OnActorHit.AddDynamic(this, &AHitActor::OnActorHit);
	//�Լ� ���ε�(OnComponentHit)
	mMesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
}

void AHitActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitActor::OnActorHit(AActor* SelfActor, AActor* OuterActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit!!"));
}

void AHitActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr,
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Explosion, this->GetActorTransform());
	/*---------------------------------------------------------------------------------------------
	�� ����ȯ : Cast<�����ϰ��� �ϴ� ����>(�����ϰ��� �ϴ� ���)
	  ����ȯ ����� ��, ������ ���� ����ȯ�� �Ϸ��� ������Ʈ�� ����ȯ ��� ������Ʈ�� ������ �˻� �õ��ϴ� ���̴�.
	  ������ �ش� ��ü�� ��ȯ�ϰ�, �ƴ� ��� nullptr�� ��ȯ�Ѵ�.
	---------------------------------------------------------------------------------------------*/
	AMyPawn* PlayerPawn = Cast<AMyPawn>(OtherActor);
	if (PlayerPawn/*PlayerPawn != nullptr*/)
	{
		UGameplayStatics::ApplyDamage((AActor*)PlayerPawn, 10.0f, nullptr, this, NULL);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Component Hit!!"));
	}
	this->Destroy();
}

