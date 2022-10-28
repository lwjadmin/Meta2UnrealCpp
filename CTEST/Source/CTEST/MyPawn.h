#pragma once

//�𸮾� ������Ʈ�� ������ �� �ִ� �ּ� ��ɸ� ����� ������� (CoreMinimal.h)
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//�𸮾� �����(UHT)���� ���������� ���� �ڵ带 �ڵ����� �������ٶ� �����ġ(���Ƿ� �����Ұ�)
#include "MyPawn.generated.h"



UCLASS() 
class CTEST_API AMyPawn : public APawn
{
	/*--------------------------------------------------------------------------------------------
	-- UCLASS() : �𸮾󿡼� �����Ǵ� Ŭ������ ��, UCLASS()�� ǥ���Ѵ�.

	-- CTEST_API : ��� �ۿ��� ������ �ʿ䰡 �ִ� �Լ��� Ŭ������ *_API ��ũ�θ� ���� ������Ѿ� �Ѵ�.
	               ��ġ extern���� ������ �ϴ� �� ����.
	-- GENERATED_BODY() : �𸮾� �����(UHT)���� ���������� ���� �ڵ带 �ڵ����� �������ٶ�, GENERATED_BODY() ��ũ�θ� ȣ���Ѵ�.
	                      ��� UCLASS���� �ʼ��̸�, �����ݷ��� �ʿ����.
	--------------------------------------------------------------------------------------------*/
	GENERATED_BODY() 
public:
	AMyPawn(); 
	//~AMyPawn(); //�𸮾� �����(UHT)���� �Ҹ��ڸ� �ڵ����� �������ְ�, �������� ������ �ݷ����� �����ϱ� ������ ������ �������� �ʴ´�.
protected:
	/*--------------------------------------------------------------------------------------------
	-- virtual : �Լ��� �����Լ��� ����Ǹ� ��ӹ޴� �ڽ�Ŭ�������� �Լ��� �������ؼ� �����ִ�. 
	             �����Լ� ȣ��� ������ ������ ������ ����Ű�� ��ü�� �����Ͽ� ȣ������ �����Ѵ�.
	-- override : �ڽ� Ŭ�������� ����Ǿ� �ִ� �����Լ�(virtual�Լ�)�� override Ű���带 �ٿ�
	              �θ� Ŭ�������� �����Լ�(virtual�Լ�)�� ������(overriding)�Ѵ�.
	-- BeginPlay() : ��Ÿ�ӿ��� ���� 1�� �����Ѵ�. 
	-- Tick() : ��Ÿ�ӿ��� �� �����Ӹ��� 1�� �����Ѵ�. 
	-- SetupPlayerInputComponent() : �𸮾� ������Ʈ ���ÿ� ���ǵ� �÷��̾� �Է��� ó���Ѵ�.
	--------------------------------------------------------------------------------------------*/
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 
public:
	void MoveForward(float value);
	void MoveRight(float value);
	void AddSphere();
	void SpawnActor();
	void SpawnMovingActor();
	void Explosion();

	//TakeDamage�� Actor�� ���ǵ� TakeDamage �Լ��� �������Ͽ� ����Ѵ�.
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	/*----------------------------------------------------------------------------------------------
	-- UPROPERTY / UFUNCTION ��ũ�� : ����� �Ӽ����� ������Ƽ ��ũ�θ� �ο��Ͽ� �����Ϳ��� ���� ������ �� �ְ� ����ų�, 
	   �������Ʈ���� ��ӹ޾� ����� �� �а��� �� �� �ֵ��� ������ �� �ִ�. 

	-- EditAnywhere : �����Ϳ��� ��������
	-- VisibleAnywhere : �����Ϳ��� ǥ��
	-- BlueprintReadWrite : �������Ʈ ��ӽ� Getter/Setter ����
	-- BlueprintReadOnly : �������Ʈ ��ӽ� Getter�� ����
	-- Category : ī�װ����� �����Ͽ� ����
	----------------------------------------------------------------------------------------------*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* RootMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* CameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* FollowCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	float MoveSpeed = 1000.0f;
};
