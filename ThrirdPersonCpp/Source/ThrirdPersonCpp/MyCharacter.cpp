// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	UIText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UIText"));


	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	
	FollowCam->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	UIText->SetupAttachment(RootComponent);
	UIText->SetText(TEXT("CPlusPlus"));
	UIText->SetTextRenderColor(FColor::Red);
	UIText->SetRelativeLocation(FVector(0, 50, 100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	//1. true : 등만 바라본다!!
	bUseControllerRotationYaw = false;
	//2. 
	SpringArm->bUsePawnControlRotation = true;
	//3.
	SpringArm->bEnableCameraLag = true;
	//4.
	SpringArm->SocketOffset.Set(0, -45, 30);
	//5.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//6.
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	//7.
	GetCharacterMovement()->JumpZVelocity = 500.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("Zoom", this, &AMyCharacter::Zoom);

}

void AMyCharacter::MoveForward(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0)
	{
		/*----------------------------------------------------------------------------------
			
		----------------------------------------------------------------------------------*/
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator Yaw(0, ControlRotation.Yaw, 0);
		FVector ForwardVector = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, AxisValue);
		//AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0)
	{
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator Yaw(0, ControlRotation.Yaw, 0);
		FVector RightVector = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightVector, AxisValue);
		//AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void AMyCharacter::Zoom(float AxisValue)
{
	SpringArm->TargetArmLength -= (AxisValue * 30.0f);
	//FMath::Clamp(SpringArm->TargetArmLength, 40.0f, 500.0f);
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    return 0.0f;
}