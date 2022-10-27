#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitActor.generated.h"

UCLASS()
class CTEST_API AHitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHitActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	//SelfActor�� �ڱ� �ڽ�, OuterActor�� �浹�� ����, NormalImpulse�� ��ݷ�, Hit : �浹�� ������ ����ִ�. 
	//Actor.h : DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams( FActorHitSignature, AActor, OnActorHit, AActor*, SelfActor, AActor*, OtherActor, FVector, NormalImpulse, const FHitResult&, Hit );
	void OnActorHit(AActor* SelfActor, AActor* OuterActor, FVector NormalImpulse, const FHitResult& Hit);

	//Oncomponent.AddDynamic ��� �� OnComponentHit ���
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
