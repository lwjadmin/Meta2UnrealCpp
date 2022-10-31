// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFlight.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

#include "Missle.h"

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_P38Body(TEXT("StaticMesh'/Game/MyContents/SM_P38_Body.SM_P38_Body'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_P38Propeller(TEXT("StaticMesh'/Game/MyContents/SM_P38_Propeller.SM_P38_Propeller'"));

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	P38Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("P38Body"));
	LeftPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftPropeller"));
	RightPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightPropeller"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	//1.
	SetRootComponent(SceneRoot);
	//2.
	P38Body->SetupAttachment(SceneRoot);
	if(SM_P38Body.Succeeded()){ P38Body->SetStaticMesh(SM_P38Body.Object); }
	//3.
	LeftPropeller->SetupAttachment(SceneRoot);
	if (SM_P38Propeller.Succeeded()) { LeftPropeller->SetStaticMesh(SM_P38Propeller.Object); }
	LeftPropeller->SetRelativeLocation(FVector(37.0f, -21.0f, 1.0f));
	//4.
	RightPropeller->SetupAttachment(SceneRoot);
	if (SM_P38Propeller.Succeeded()) { RightPropeller->SetStaticMesh(SM_P38Propeller.Object); }
	RightPropeller->SetRelativeLocation(FVector(37.0f, 21.0f, 1.0f));
	//5.
	SpringArm->SetupAttachment(SceneRoot);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	//6.
	Camera->SetupAttachment(SpringArm);
	//7.
	Movement->MaxSpeed = MoveSpeed;
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LeftPropeller->AddLocalRotation(FRotator(0, 0, PropellerRotationSpeed * DeltaTime));
	RightPropeller->AddLocalRotation(FRotator(0, 0, PropellerRotationSpeed * DeltaTime));
	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &APlayerFlight::Roll);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &APlayerFlight::Pitch);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerFlight::Fire);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &APlayerFlight::BoostStart);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &APlayerFlight::BoostFinish);
}

void APlayerFlight::Pitch(float value)
{
	AddActorLocalRotation(FRotator(FMath::Clamp<float>(value, -1, 1) * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),0,0));
}

void APlayerFlight::Roll(float value)
{
	AddActorLocalRotation(FRotator(0, 0, FMath::Clamp<float>(value, -1, 1) * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void APlayerFlight::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("FIRE"));
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	FRotator rotator = GetActorRotation();
	FVector relativelocation(0, 0, -5);
	FVector spawnLocation = GetActorLocation() + relativelocation;
	GetWorld()->SpawnActor<AMissle>(AMissle::StaticClass(), spawnLocation, rotator, spawnParams);
}

void APlayerFlight::BoostStart()
{
	Movement->MaxSpeed = MoveSpeed * 2;
}

void APlayerFlight::BoostFinish()
{
	Movement->MaxSpeed = MoveSpeed * 1;
}


