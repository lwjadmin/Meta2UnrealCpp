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
	//생성자 : 변수 세팅보다 생성자가 먼저 호출되기 때문에, 언리얼 변수에 메쉬를 할당해도 여기서는 nullptr로 보인다.
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

//컨스트럭션 스크립트를 C++로 사용하는 방법!!!
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
	//	//CDO에서 생성된 Class를 복사한 카피본을 만들고, 오브젝트 레퍼런스 포인터(UUserWidget*)가 class의 주소를 가리키게 한다.
	//  //호출할때마다 카피본이 계속 생성된다.
	//	UUserWidget* widget2 = CreateWidget<UUserWidget>(GetWorld(), Widget_Class);
	//	widget2->AddToViewport();
	//}
	
	////CASE A.TSoftClassPtr<UUserWidget> Loading - Synchronous
	//if (Widget_SoftClass)
	//{
	//	//동기적으로 로드하고(필요한 경우) 자산 Ptr이 나타내는 자산 개체를 반환한다.
	// /* 메모리에 없으면 만들어서 포인터를 주고, 있으면 포인터만 주고 */
	//	UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), Widget_SoftClass.LoadSynchronous());
	//	ui->AddToViewport();
	//}

	////CASE B.TSoftClassPtr<UUserWidget> Loading - Asynchronous
	//if (Widget_SoftClass)
	//{
	//	/* 엔진 내부 에셋 관리자에서 해당 에셋이 메모리에 로드되면 포인터를 주도록 */
	//	auto& assetLoader = UAssetManager::GetStreamableManager();
	//	assetLoader.RequestAsyncLoad(Widget_SoftClass.ToStringReference(), FStreamableDelegate::CreateUObject(this, &AFirePartcleActor::OnAsset));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Widget_SoftClass.ToStringReference().ToString());
	//}
	
	//CASE A. TSoftObjectPtr<UStaticMesh> Loading - Synchronous
	if (SoftMesh)
	{
		/* Synchronously load (if necessary) and return the asset object represented by this asset ptr */
		/* 메모리에 없으면 만들어서 포인터를 주고, 있으면 포인터만 주고 */
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
		/* 엔진 내부 에셋 관리자에서 해당 에셋이 메모리에 로드되면 포인터를 주도록 */
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
	Get() 소프트 포인터 역참조
	@return nullptr이 객체가 없거나 소프트 포인터가 null이면 유효하지 않은 UClass 포인터
	----------------------------------------------------------------------------*/
	UUserWidget* ui = CreateWidget<UUserWidget>(GetWorld(), Widget_SoftClass.Get());
	ui->AddToViewport();
}

