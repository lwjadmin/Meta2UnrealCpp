// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h" //For DrawDebugLine()


// Sets default values
APlayerPawn::APlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //static ConstructorHelpers::FObjectFinder<UStaticMesh>
    //	SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    //static ConstructorHelpers::FObjectFinder<UMaterial>
    //	BasicMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
    //
    //RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
    //RootMesh->SetStaticMesh(SphereMesh.Object);
    //RootMesh->SetMaterial(0, BasicMaterial.Object);
    //RootMesh->SetCollisionObjectType(ECC_Pawn);
    //RootMesh->SetGenerateOverlapEvents(true);
    //RootComponent = RootMesh;
    //
    //CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
    //FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
    //CameraArm->AttachTo(RootMesh); //AttachTo로 해당 컴포넌트의 하위로 붙일 수 있다!!
    ////FRotator(Y,X,Z)
    //CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-30.0f, 0.0f, 0.0f));
    //CameraArm->TargetArmLength = 400.0f;
    //CameraArm->bEnableCameraLag = true;
    //CameraArm->CameraLagSpeed = 3.0f;
    //CameraArm->bDoCollisionTest = false;
    //FollowCam->AttachTo(CameraArm);

    //컨트롤러 로테이션 값을 사용한다.
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = true;

    //UMG로 에임을 표시하기 전단계 : 구체를 만들어 조준점역할을 하도록 만든다.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> m_sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    UStaticMeshComponent* Aim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AimComponent"));
    Aim->SetStaticMesh(m_sphere.Object);
    Aim->SetRelativeLocation(FVector(300, 0, 0));
    Aim->AttachTo(RootComponent);
    Aim->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
    PlayerInputComponent->BindAction(TEXT("LeftMouseButton"), IE_Pressed, this, &APlayerPawn::MouseButtonClick);
}

void APlayerPawn::MoveForward(float value)
{
    bool bSweep = true;
    AddActorWorldOffset(FVector(value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0), bSweep);
}

void APlayerPawn::MoveRight(float value)
{
    bool bSweep = true;
    AddActorWorldOffset(FVector(0, value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0), bSweep);
}

void APlayerPawn::MouseButtonClick()
{
    /*-----------------------------------------------------------------------------------------
        LineTraceByChannel을 사용하여 Ray를 쏘고, 닿은 Actor에게 Apply Damage(TakeDamage)
    -----------------------------------------------------------------------------------------*/
    //시작점과 끝점 설정
    const FVector Start = this->GetActorLocation(); //현재 Pawn의 위치
    const FVector Direction = GetActorRotation().Vector(); //현재 Pawn의 Rotation 방향 벡터
    const FVector End = Start + (Direction * 10000.0f); //방향벡터 * 10000.0f(스칼라) = 끝벡터

    //결과값을 담을 지역변수
    FHitResult Hit;
    //트레이스 파라미터 설정
    FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
    //복잡한 충돌을 추적해야 하는지 여부(?)
    TraceParams.bTraceComplex = true;
    //복잡한 정적 메쉬 추격을 위해 삼각형면 인덱스를 반환할 지 여부(?)
    TraceParams.bReturnFaceIndex = false;
    //자신을 무시한다.
    TraceParams.AddIgnoredActor(this);
    //라인트레이스 디버그를 표시하는 방법
    FName TraceTag = TEXT("None"/*Persistent*/);
    GetWorld()->DebugDrawTraceTag = TraceTag;
    TraceParams.TraceTag = TraceTag;
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

    //FHitResult : 블루프린트에서 LineTraceByChannel -> Out Hit을 Break했을 때, 속성들을 확인할 수 있다.
    if (Hit.GetActor())
    {
        Hit.GetActor()->TakeDamage(10, FDamageEvent(), NULL, this);
    }
    //뷰포트 PrintString
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Fire!"));
    //빨간색 라인을 그린다.
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);
}