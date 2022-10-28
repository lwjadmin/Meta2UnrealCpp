/*---------------------------------------------------------------------------------------
	헤더파일에 Include를 걸어두면 컴파일 시간이 늘어나고, 의존성이 높아지는 단점이 있다.
	CPP파일에 Include를 걸어두어야 컴파일 시간을 줄일 수 있다.
	클래스의 메인 헤더파일 인클루드[#include "MyPawn.h"]는 맨 위에 배치하는 것이 좋다.
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
 	//Tick을 호출할 거면 true(기본값), 호출하지 않을 거면 false
	PrimaryActorTick.bCanEverTick = true;

	/*-------------------------------------------------------------------------
		※ ConstructorHelpers & CreateDefaultSubObject 
		   UObject의 생성자(Constructor)에서만 호출한다. 
		   레퍼런스 주소는 언리얼 에디터에서 우측마우스 클릭 > 레퍼런스 복사를 클릭하면 된다.
		   엔진에서 싱글턴처럼 최초 호출될때 한번 만들어놓고 만든 포인터만 넘겨주는 것 같다. 

		※ CreateDefaultSubObject
		   노드명이 겹치면 안된다!! 빌드는 되는데 런타임에서 죽는다!
		   널체크 & 예외체크를 해주는 것이 좋긴하다.
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
	CameraArm->AttachTo(RootMesh); //AttachTo로 해당 컴포넌트의 하위로 붙일 수 있다!!
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
	//출력 로그 Print
	//Warning : 노랑, Fatal : 빨강...
	//UE_LOG(LogTemp, Warning, TEXT("Warning Tick"));
	//UE_LOG(LogTemp, Fatal, TEXT("Fatal Tick"));
	//UE_LOG(LogTemp, Error, TEXT("Error Tick"));
	//UE_LOG(LogTemp, Warning, TEXT("Warning Tick"));
	//UE_LOG(LogTemp, Display, TEXT("Display Tick"));
	//UE_LOG(LogTemp, Log, TEXT("Log Tick"));
	//UE_LOG(LogTemp, Verbose, TEXT("Verbose Tick"));
	//UE_LOG(LogTemp, VeryVerbose, TEXT("VeryVerbose Tick"));

	//에디터 뷰포트 Print
	//3초, 파란색, 텍스트 
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
	//프로젝트 셋팅 > 엔진 > 입력에 정의된 입력 축매핑, 입력 액션매핑을 사용하여 처리를 한다. 
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
	UObject의 런타임에서만 호출한다.
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
	  이 구성요소를 등록하여 렌더링/물리적 상태를 만든다.
	  아직 존재하지 않을 경우 외부 Actor의 Components 배열에도 자신을 추가한다.
	-------------------------------------------------------------------------*/
	NewSphere->RegisterComponent();
}

void AMyPawn::SpawnActor()
{
	//struct FActorSpawnParameters : Collision Handling Override + Owner를 포함한다. 
	FActorSpawnParameters spawnInfo = FActorSpawnParameters();
	/*----------------------------------------------------------
	DisplayName = "Default" :  Undefined
	DisplayName = "Always Spawn, Ignore Collisions" : AlwaysSpawn
	DisplayName = "Try To Adjust Location, But Always Spawn" : AdjustIfPossibleButAlwaysSpawn
	DisplayName = "Try To Adjust Location, Don't Spawn If Still Colliding" : AdjustIfPossibleButDontSpawnIfColliding
	DisplayName = "Do Not Spawn" : DontSpawnIfColliding

	SpawnActor<class>
	레벨에서 location과 rotation 정보를 갖는 액터를 스폰하기 위한 함수이다.
	UObject 생성자에서 호출하면 안된다.
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


	//1. TActorIterator으로 액터찾기(UWorld 오브젝트(GetWorld() 필요)
	for (TActorIterator<AMyActor> actor(GetWorld()); actor; ++actor)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GWorld, FX_Explosion, actor->GetActorTransform());
		actor->Destroy();
	}

	//2. TActorRange로 액터찾기(UWorld 오브젝트(GetWorld() 필요)
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

//대미지를 받았을 때 처리(AnyDamage)
float AMyPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("TakeDamage"));
	return 0.0f;
}
