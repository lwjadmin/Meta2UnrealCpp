
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

	//물리 적용
	//mMesh->SetSimulatePhysics(true);
	mMesh->SetSimulatePhysics(false);
	//시뮬레이션을 Hit Event가 동작하도록 설정(Simulation Generates Hit Events [Check : true / Uncheck : false]
	mMesh->SetNotifyRigidBodyCollision(true);
	

	//함수 바인딩(OnActorHit)
	//this->OnActorHit.AddDynamic(this, &AHitActor::OnActorHit);
	//함수 바인딩(OnComponentHit)
	//mMesh->OnComponentHit.AddDynamic(this, &AHitActor::OnComponentHit);
	mMesh->OnComponentBeginOverlap.AddDynamic(this, &AHitActor::OnOverlapBegin);
	//Generate Overlap Events [Check : true / Uncheck : false]
	mMesh->SetGenerateOverlapEvents(true);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//MyActorComponent2 추가
	UMyActorComponent2* customComponent = CreateDefaultSubobject<UMyActorComponent2>(TEXT("customComponent"));
	
	//컴포넌트 태그를 추가한다.
	customComponent->ComponentTags.Add(FName(TEXT("move")));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//충돌 처리
	//콜리전 타입 설정 
	mMesh->SetCollisionObjectType(ECC_WorldDynamic);
	//자신과의 충돌 방지
	mMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	//폰 힛 가능하게 설정
	//mMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	//폰 오버랩 가능하게 설정
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
	※ 형변환 : Cast<변경하고자 하는 유형>(변경하고자 하는 대상)
	  형변환 사용할 때, 간단히 말해 형변환을 하려는 오브젝트가 형변환 대상 오브젝트와 같은지 검사 시도하는 것이다.
	  있으면 해당 객체를 반환하고, 아닐 경우 nullptr를 반환한다.
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

