// Fill out your copyright notice in the Description page of Project Settings.


#include "Missle.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AMissle::AMissle()
{
	/*-------------------------------------------------------------------------------
	** PrimaryActorTick.bCanEverTick 
	   true  : �� �����Ӹ��� Tick�� ȣ��ȴ�.
	   false : �� �����Ӹ��� Tick�� ȣ����� �ʴ´�.

	** �����ڿ����� CreateDefaultSubobject�ؼ� ������Ʈ ����/���Ḹ ���ִ� �� ����, ������Ʈ�� ������ 
	   �����ڿ��� �ص� ��� �ȉ�� �Ҽ� �ֱ� ������ PreInitializeComponents���� �ϴ���
	   �ƴϸ� BeginPlay���� �ϴ� ���� �����Ѵ�.
	-------------------------------------------------------------------------------*/
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_Missle(TEXT("StaticMesh'/Game/MyContents/SM_Rocket.SM_Rocket'"));

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	MissleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissleBody"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(SceneRoot);
	Capsule->SetupAttachment(SceneRoot);
	Capsule->SetRelativeRotation(FRotator(-90, 0, 0));
	Capsule->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.65f));

	MissleBody->SetupAttachment(SceneRoot);
	MissleBody->SetRelativeRotation(FRotator(-90, 0, 0));
	MissleBody->SetStaticMesh(SM_Missle.Object);

	if (bIsDropBomb == true)
	{
		Movement->ProjectileGravityScale = 1.0f;
		Movement->InitialSpeed = 750.0f;
		Movement->MaxSpeed = 750.0f;
	}
	else
	{
		Movement->ProjectileGravityScale = 0.0f;
		Movement->InitialSpeed = 1500.0f;
		Movement->MaxSpeed = 2000.0f;
	}
}

// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	/*-------------------------------------------------------------------------------
	-- Hit Event : �������� ��ź
	   Channel : Block && 
	             Simulate Physics = true && 
	             Simulation Generates Hit Events = true�̾�� �Ѵ�!
	-- Overlap Event : �̻���
	   Channel : Overlap && 
	             Generate Overlap Events = true && 
	             Overlap ����� Generate Overlap Events = true�̾�� �Ѵ�!!
	-------------------------------------------------------------------------------*/
	if (bIsDropBomb == true)
	{
		Capsule->SetSimulatePhysics(true);
		Capsule->SetNotifyRigidBodyCollision(true);
		Capsule->SetGenerateOverlapEvents(false);
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionObjectType(ECC_WorldDynamic);
		Capsule->SetCollisionResponseToAllChannels(ECR_Block);
		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		Capsule->OnComponentHit.AddDynamic(this, &AMissle::OnComponentHit);
		//Capsule->OnComponentHit.RemoveDynamic(this, &AMissle::OnComponentHit);
	}
	else
	{
		Capsule->SetNotifyRigidBodyCollision(false);
		Capsule->SetGenerateOverlapEvents(true);
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionObjectType(ECC_WorldDynamic);
		Capsule->SetCollisionResponseToAllChannels(ECR_Overlap);
		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMissle::OnComponentBeginOverlap);
		//Capsule->OnComponentBeginOverlap.RemoveDynamic(this, &AMissle::OnComponentBeginOverlap); 
		//HIT : �� �ȵǳ�...
		//Capsule->SetSimulatePhysics(false);
		//Capsule->SetEnableGravity(false);
		//Capsule->SetNotifyRigidBodyCollision(true);
		//Capsule->SetGenerateOverlapEvents(false);
		//Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Capsule->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
		//Capsule->SetCollisionObjectType(ECC_WorldDynamic);
		//Capsule->SetCollisionResponseToAllChannels(ECR_Block);
		//Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		//Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		//Capsule->OnComponentHit.AddDynamic(this, &AMissle::OnComponentHit);
	}
	GetWorld()->GetTimerManager().SetTimer(SelfDestructTimer, this, &AMissle::SelfDestruct, 3.0f, false);
}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMissle::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("HIT!"));
	SelfDestruct();
}

void AMissle::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("OVERLAP!"));
	SelfDestruct();
}

void AMissle::SelfDestruct()
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, 
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Explosion,GetActorTransform());
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/StarterContent/Audio/Starter_Background_Cue.Starter_Background_Cue'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	Destroy();
}
