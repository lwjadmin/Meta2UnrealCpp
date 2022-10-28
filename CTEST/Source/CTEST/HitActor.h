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

    //
    UFUNCTION()
        //SelfActor�� �ڱ� �ڽ�, OuterActor�� �浹�� ����, NormalImpulse�� ��ݷ�, Hit : �浹�� ������ ����ִ�. 
        //Actor.h : DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams( FActorHitSignature, AActor, OnActorHit, AActor*, SelfActor, AActor*, OtherActor, FVector, NormalImpulse, const FHitResult&, Hit );
        void OnActorHit
        (
            AActor* SelfActor,
            AActor* OuterActor,
            FVector NormalImpulse,
            const FHitResult& Hit
        );

    //Oncomponent.AddDynamic ��� �� OnComponentHit ���
    UFUNCTION()
        void OnComponentHit
        (
            class UPrimitiveComponent* HitComponent,
            AActor* OtherActor,
            class UPrimitiveComponent* OtherComp,
            FVector NormalImpulse,
            const FHitResult& Hit
        );

    //UPrimitiveComponent*, OverlappedComponent, 
    //    AActor*, OtherActor, 
    //    UPrimitiveComponent*, OtherComp, 
    //    int32, OtherBodyIndex, 
    //    bool, bFromSweep, 
    //    const FHitResult&, SweepResult
    //    );
    UFUNCTION()
        void OnOverlapBegin
        (
            class UPrimitiveComponent* OverlappedComponent,
            AActor* OtherActor,
            class UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bFromSweep,
            const FHitResult& SweepResult
        );

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        class UStaticMeshComponent* mMesh;

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

};
