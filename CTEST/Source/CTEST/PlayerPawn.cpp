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
    //CameraArm->AttachTo(RootMesh); //AttachTo�� �ش� ������Ʈ�� ������ ���� �� �ִ�!!
    ////FRotator(Y,X,Z)
    //CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-30.0f, 0.0f, 0.0f));
    //CameraArm->TargetArmLength = 400.0f;
    //CameraArm->bEnableCameraLag = true;
    //CameraArm->CameraLagSpeed = 3.0f;
    //CameraArm->bDoCollisionTest = false;
    //FollowCam->AttachTo(CameraArm);

    //��Ʈ�ѷ� �����̼� ���� ����Ѵ�.
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = true;

    //UMG�� ������ ǥ���ϱ� ���ܰ� : ��ü�� ����� ������������ �ϵ��� �����.
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
        LineTraceByChannel�� ����Ͽ� Ray�� ���, ���� Actor���� Apply Damage(TakeDamage)
    -----------------------------------------------------------------------------------------*/
    //�������� ���� ����
    const FVector Start = this->GetActorLocation(); //���� Pawn�� ��ġ
    const FVector Direction = GetActorRotation().Vector(); //���� Pawn�� Rotation ���� ����
    const FVector End = Start + (Direction * 10000.0f); //���⺤�� * 10000.0f(��Į��) = ������

    //������� ���� ��������
    FHitResult Hit;
    //Ʈ���̽� �Ķ���� ����
    FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
    //������ �浹�� �����ؾ� �ϴ��� ����(?)
    TraceParams.bTraceComplex = true;
    //������ ���� �޽� �߰��� ���� �ﰢ���� �ε����� ��ȯ�� �� ����(?)
    TraceParams.bReturnFaceIndex = false;
    //�ڽ��� �����Ѵ�.
    TraceParams.AddIgnoredActor(this);
    //����Ʈ���̽� ����׸� ǥ���ϴ� ���
    FName TraceTag = TEXT("None"/*Persistent*/);
    GetWorld()->DebugDrawTraceTag = TraceTag;
    TraceParams.TraceTag = TraceTag;
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

    //FHitResult : �������Ʈ���� LineTraceByChannel -> Out Hit�� Break���� ��, �Ӽ����� Ȯ���� �� �ִ�.
    if (Hit.GetActor())
    {
        Hit.GetActor()->TakeDamage(10, FDamageEvent(), NULL, this);
    }
    //����Ʈ PrintString
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Fire!"));
    //������ ������ �׸���.
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);
}