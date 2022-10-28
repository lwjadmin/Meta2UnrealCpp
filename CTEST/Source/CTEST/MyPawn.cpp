/*---------------------------------------------------------------------------------------
	������Ͽ� Include�� �ɾ�θ� ������ �ð��� �þ��, �������� �������� ������ �ִ�.
	CPP���Ͽ� Include�� �ɾ�ξ�� ������ �ð��� ���� �� �ִ�.
	Ŭ������ ���� ������� ��Ŭ���[#include "MyPawn.h"]�� �� ���� ��ġ�ϴ� ���� ����.
---------------------------------------------------------------------------------------*/
#include "MyPawn.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/Material.h"


#include "MyActor.h"
#include "MovingActor.h"

AMyPawn::AMyPawn()
{
 	//Tick�� ȣ���� �Ÿ� true(�⺻��), ȣ������ ���� �Ÿ� false
	PrimaryActorTick.bCanEverTick = true;

	/*-------------------------------------------------------------------------
		�� ConstructorHelpers & CreateDefaultSubObject 
		   UObject�� ������(Constructor)������ ȣ���Ѵ�. 
		   ���۷��� �ּҴ� �𸮾� �����Ϳ��� �������콺 Ŭ�� > ���۷��� ���縦 Ŭ���ϸ� �ȴ�.
		   �������� �̱���ó�� ���� ȣ��ɶ� �ѹ� �������� ���� �����͸� �Ѱ��ִ� �� ����. 

		�� CreateDefaultSubObject
		   ������ ��ġ�� �ȵȴ�!! ����� �Ǵµ� ��Ÿ�ӿ��� �״´�!
		   ��üũ & ����üũ�� ���ִ� ���� �����ϴ�.
	-------------------------------------------------------------------------*/
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		BasicMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));

	RootMesh->SetStaticMesh(SphereMesh.Object);
	RootMesh->SetMaterial(0, BasicMaterial.Object);
	RootComponent = RootMesh;
	//SetRootComponent(mMesh);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	CameraArm->AttachTo(RootMesh); //AttachTo�� �ش� ������Ʈ�� ������ ���� �� �ִ�!!
	//FRotator(Y,X,Z)
	CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-30.0f, 0.0f, 0.0f));
	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 3.0f;
	CameraArm->bDoCollisionTest = false;
	FollowCam->AttachTo(CameraArm);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//��� �α� Print
	//Warning : ���, Fatal : ����...
	//UE_LOG(LogTemp, Warning, TEXT("Warning Tick"));
	//UE_LOG(LogTemp, Fatal, TEXT("Fatal Tick"));
	//UE_LOG(LogTemp, Error, TEXT("Error Tick"));
	//UE_LOG(LogTemp, Warning, TEXT("Warning Tick"));
	//UE_LOG(LogTemp, Display, TEXT("Display Tick"));
	//UE_LOG(LogTemp, Log, TEXT("Log Tick"));
	//UE_LOG(LogTemp, Verbose, TEXT("Verbose Tick"));
	//UE_LOG(LogTemp, VeryVerbose, TEXT("VeryVerbose Tick"));

	//������ ����Ʈ Print
	//3��, �Ķ���, �ؽ�Ʈ 
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("AddSphere!"));
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//������Ʈ ���� > ���� > �Է¿� ���ǵ� �Է� �����, �Է� �׼Ǹ����� ����Ͽ� ó���� �Ѵ�. 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAction(TEXT("AddSphere"), IE_Pressed,this, &AMyPawn::AddSphere);
	PlayerInputComponent->BindAction(TEXT("SpawnActor"), IE_Pressed, this, &AMyPawn::SpawnActor);
	PlayerInputComponent->BindAction(TEXT("SpawnMovingActor"), IE_Pressed, this, &AMyPawn::SpawnMovingActor);
	PlayerInputComponent->BindAction(TEXT("Explosion"), IE_Pressed, this, &AMyPawn::Explosion);
	//PlayerInputComponent->BindAction(TEXT("Explosion"), IE_Released, this, &AMyPawn::Explosion);
}

void AMyPawn::MoveForward(float value)
{
	AddActorWorldOffset(FVector(value* MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0));
}

void AMyPawn::MoveRight(float value)
{
	AddActorWorldOffset(FVector(0, value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0));
}

void AMyPawn::AddSphere()
{
	/*-------------------------------------------------------------------------
	NewObject<Class> & LoadObject 
	UObject�� ��Ÿ�ӿ����� ȣ���Ѵ�.
	-------------------------------------------------------------------------*/
	UStaticMeshComponent* NewSphere = NewObject<UStaticMeshComponent>(this,
		UStaticMeshComponent::StaticClass(), FName("AddSphere"));
	UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr,
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	UMaterial* mat = LoadObject<UMaterial>(nullptr,
		TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	NewSphere->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
	NewSphere->SetRelativeLocation(FVector(0, 0, 100));
	NewSphere->SetMaterial(0, mat);
	NewSphere->SetStaticMesh(mesh);

	/*-------------------------------------------------------------------------
	  �� ������Ҹ� ����Ͽ� ������/������ ���¸� �����.
	  ���� �������� ���� ��� �ܺ� Actor�� Components �迭���� �ڽ��� �߰��Ѵ�.
	-------------------------------------------------------------------------*/
	NewSphere->RegisterComponent();
}

void AMyPawn::SpawnActor()
{
	//struct FActorSpawnParameters : Collision Handling Override + Owner�� �����Ѵ�. 
	FActorSpawnParameters spawnInfo = FActorSpawnParameters();
	/*----------------------------------------------------------
	DisplayName = "Default" :  Undefined
	DisplayName = "Always Spawn, Ignore Collisions" : AlwaysSpawn
	DisplayName = "Try To Adjust Location, But Always Spawn" : AdjustIfPossibleButAlwaysSpawn
	DisplayName = "Try To Adjust Location, Don't Spawn If Still Colliding" : AdjustIfPossibleButDontSpawnIfColliding
	DisplayName = "Do Not Spawn" : DontSpawnIfColliding

	SpawnActor<class>
	�������� location�� rotation ������ ���� ���͸� �����ϱ� ���� �Լ��̴�.
	UObject �����ڿ��� ȣ���ϸ� �ȵȴ�.
	Blueprint : SpawnActorFromClass
	---------------------------------------------------------*/
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
	GetWorld()->SpawnActor<AMyActor>(this->GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
}


void AMyPawn::SpawnMovingActor()
{
	FActorSpawnParameters spawnInfo = FActorSpawnParameters();
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AMovingActor>(this->GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
}

void AMyPawn::Explosion()
{
	UParticleSystem* FX_Explosion = LoadObject<UParticleSystem>(nullptr, 
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));


	//1. TActorIterator���� ����ã��(UWorld ������Ʈ(GetWorld() �ʿ�)
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
		actor->Destroy();
	}

	//2. TActorRange�� ����ã��(UWorld ������Ʈ(GetWorld() �ʿ�)
	//for (auto MovingActor : TActorRange<AMovingActor>(GetWorld()))
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, MovingActor->GetActorTransform());
	//	MovingActor->Destroy();
	//}

	for (auto Actor : TActorRange<AActor>(GetWorld()))
	{
		AMovingActor* MovingActor = Cast<AMovingActor>(Actor);
		if (MovingActor != nullptr)
		{
			MovingActor->bIsSmaller = true;
		}
	}
}

//������� �޾��� �� ó��(AnyDamage)
float AMyPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("TakeDamage"));
	return 0.0f;
}
