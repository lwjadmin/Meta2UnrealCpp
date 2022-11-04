// Fill out your copyright notice in the Description page of Project Settings.


#include "FirePartcleActor.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"

#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

// Sets default values
AFirePartcleActor::AFirePartcleActor()
{
	//������ : ���� ���ú��� �����ڰ� ���� ȣ��Ǳ� ������, �𸮾� ������ �޽��� �Ҵ��ص� ���⼭�� nullptr�� ���δ�.
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

//����Ʈ���� ��ũ��Ʈ�� C++�� ����ϴ� ���!!!
void AFirePartcleActor::OnConstruction(const FTransform& Transform)
{
	if (BaseMesh)
	{
		MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName("MeshComponent"));
		MeshComponent->AttachTo(SceneRoot, NAME_None, EAttachLocation::SnapToTarget);
		MeshComponent->SetStaticMesh(BaseMesh);
		MeshComponent->RegisterComponent();
	}
}

// Called when the game starts or when spawned
void AFirePartcleActor::BeginPlay()
{
	Super::BeginPlay();

	FX_Fire = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (FX_Fire)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Fire, GetActorTransform());
	}

	////CASE A.Default (Class Instance Reference)
	//if (Widget_Class)
	//{
	//	//CDO���� ������ Class�� ������ ī�Ǻ��� �����, ������Ʈ ���۷��� ������(UUserWidget*)�� class�� �ּҸ� ����Ű�� �Ѵ�.
	//  //ȣ���Ҷ����� ī�Ǻ��� ��� �����ȴ�.
	//	UUserWidget* widget2 = CreateWidget<UUserWidget>(GetWorld(), Widget_Class);
	//	widget2->AddToViewport();
	//}
	
	////CASE A.TSoftClassPtr<UUserWidget> Loading - Synchronous
	//if (Widget_SoftClass)
	//{
	//	//���������� �ε��ϰ�(�ʿ��� ���) �ڻ� Ptr�� ��Ÿ���� �ڻ� ��ü�� ��ȯ�Ѵ�.
	// /* �޸𸮿� ������ ���� �����͸� �ְ�, ������ �����͸� �ְ� */
	//	UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), Widget_SoftClass.LoadSynchronous());
	//	ui->AddToViewport();
	//}

	////CASE B.TSoftClassPtr<UUserWidget> Loading - Asynchronous
	//if (Widget_SoftClass)
	//{
	//	/* ���� ���� ���� �����ڿ��� �ش� ������ �޸𸮿� �ε�Ǹ� �����͸� �ֵ��� */
	//	auto& assetLoader = UAssetManager::GetStreamableManager();
	//	assetLoader.RequestAsyncLoad(Widget_SoftClass.ToStringReference(), FStreamableDelegate::CreateUObject(this, &AFirePartcleActor::OnAsset));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Widget_SoftClass.ToStringReference().ToString());
	//}
	
	//CASE A. TSoftObjectPtr<UStaticMesh> Loading - Synchronous
	if (SoftMesh)
	{
		/* Synchronously load (if necessary) and return the asset object represented by this asset ptr */
		/* �޸𸮿� ������ ���� �����͸� �ְ�, ������ �����͸� �ְ� */
		UStaticMesh* SM_Mesh = SoftMesh.LoadSynchronous();
		if (SM_Mesh)
		{
			UStaticMeshComponent* ConeComp = NewObject<UStaticMeshComponent>(this,
				UStaticMeshComponent::StaticClass(), FName("RootMeshComp"));
			
			ConeComp->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
			ConeComp->SetRelativeLocation(FVector(0, 0, 100));
			ConeComp->SetStaticMesh(SM_Mesh);
			ConeComp->RegisterComponent();
		}
	}

	//CASE B. TSoftObjectPtr<UStaticMesh> Loading - Asynchronous
	if (SoftMesh)
	{
		/* ���� ���� ���� �����ڿ��� �ش� ������ �޸𸮿� �ε�Ǹ� �����͸� �ֵ��� */
		/* Accesses the StreamableManager used by this Asset Manager. Static for easy access */
		auto& assetLoader = UAssetManager::GetStreamableManager();
		// Schedule a new callback, this will get called when all related async loads are completed
		assetLoader.RequestAsyncLoad(SoftMesh.ToStringReference(), FStreamableDelegate::CreateUObject(this, &AFirePartcleActor::OnMeshCreation));
	}
}

// Called every frame
void AFirePartcleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirePartcleActor::OnMeshCreation()
{
	UStaticMeshComponent* ConeComp = NewObject<UStaticMeshComponent>(this,
		UStaticMeshComponent::StaticClass(), FName("ConeComp"));
	ConeComp->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
	ConeComp->SetRelativeLocation(FVector(0, 0, 100));
	ConeComp->SetStaticMesh(SoftMesh.Get());
	ConeComp->RegisterComponent();
}

void AFirePartcleActor::OnAsset()
{
	/*----------------------------------------------------------------------------
	Get() ����Ʈ ������ ������
	@return nullptr�� ��ü�� ���ų� ����Ʈ �����Ͱ� null�̸� ��ȿ���� ���� UClass ������
	----------------------------------------------------------------------------*/
	UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), Widget_SoftClass.Get());
	ui->AddToViewport();
}

