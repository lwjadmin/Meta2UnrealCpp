
#include "HitActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"
#include "MyPawn.h"
#include "MyActorComponent2.h"


AHitActor::AHitActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial>
		m_colormat(TEXT("Material'/Game/Materials/M_Color.M_Color'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		m_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

    mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComponent"));
	UMaterialInstanceDynamic* mi_colormat = UMaterialInstanceDynamic::Create(m_colormat.Object, mMesh);

	RootComponent = mMesh;
	mMesh->SetStaticMesh(m_Sphere.Object);
	float colorR = FMath::FRandRange(0, 1);
	float colorG = FMath::FRandRange(0, 1);
	float colorB = FMath::FRandRange(0, 1);

	mi_colormat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(colorR, colorG, colorB));
	mMesh->SetMaterial(0, mi_colormat);

	//���� ����
	//mMesh->SetSimulatePhysics(true);
	mMesh->SetSimulatePhysics(false);
	//�ùķ��̼��� Hit Event�� �����ϵ��� ����(Simulation Generates Hit Events [Check : true / Uncheck : false]
	mMesh->SetNotifyRigidBodyCollision(true);
	

	//�Լ� ���ε�(OnActorHit)
	//this->OnActorHit.AddDynamic(this, &AHitActor::OnActorHit);
	//�Լ� ���ε�(OnComponentHit)
	//mMesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
	mMesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnOverlapBegin);
	//Generate Overlap Events [Check : true / Uncheck : false]
	mMesh->SetGenerateOverlapEvents(true);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//MyActorComponent2 �߰�
	UMyActorComponent2* customComponent = CreateDefaultSubobject<UMyActorComponent2>(TEXT("customComponent"));
	
	//������Ʈ �±׸� �߰��Ѵ�.
	customComponent->ComponentTags.Add(FName(TEXT("move")));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�浹 ó��
	//�ݸ��� Ÿ�� ���� 
	mMesh->SetCollisionObjectType(ECC_WorldDynamic);
	//�ڽŰ��� �浹 ����
	mMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	//�� �� �����ϰ� ����
	//mMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	//�� ������ �����ϰ� ����
	mMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AHitActor::BeginPlay()
{
	Super::BeginPlay();

	//GetComponenets;

	for (UActorComponent* ActComp : GetComponents())
	{
		if (ActComp->ComponentHasTag(FName(TEXT("move"))))
		{
			UMyActorComponent2* CustComp = Cast<UMyActorComponent2>(ActComp);
			AActor* Target = GetWorld()->GetFirstPlayerController()->GetPawn();
			CustComp->SetFollowTarget(Target,0.5f);
		}
	}
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

void AHitActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString msg = FString::Printf(TEXT("Overlapped Actor : %s"), *OtherActor->GetActorLabel());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, msg);
}

float AHitActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UParticleSystem* FxExplosion = LoadObject<UParticleSystem>(nullptr,
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FxExplosion, this->GetActorTransform());
	this->Destroy();
	return 0.0f;
}

