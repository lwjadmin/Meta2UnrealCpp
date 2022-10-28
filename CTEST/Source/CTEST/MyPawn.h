#pragma once

//언리얼 오브젝트가 동작할 수 있는 최소 기능만 선언된 헤더파일 (CoreMinimal.h)
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//언리얼 헤더툴(UHT)에서 엔진컨텐츠 관련 코드를 자동으로 생성해줄때 헤더위치(임의로 수정불가)
#include "MyPawn.generated.h"



UCLASS() 
class CTEST_API AMyPawn : public APawn
{
	/*--------------------------------------------------------------------------------------------
	-- UCLASS() : 언리얼에서 관리되는 클래스일 때, UCLASS()로 표기한다.

	-- CTEST_API : 모듈 밖에서 접근할 필요가 있는 함수의 클래스는 *_API 매크로를 통해 노출시켜야 한다.
	               마치 extern같은 역할을 하는 것 같다.
	-- GENERATED_BODY() : 언리얼 헤더툴(UHT)에서 엔진컨텐츠 관련 코드를 자동으로 생성해줄때, GENERATED_BODY() 매크로를 호출한다.
	                      모든 UCLASS에서 필수이며, 세미콜론이 필요없다.
	--------------------------------------------------------------------------------------------*/
	GENERATED_BODY() 
public:
	AMyPawn(); 
	//~AMyPawn(); //언리얼 헤더툴(UHT)에서 소멸자를 자동으로 생성해주고, 엔진에서 가비지 콜렉션을 수행하기 때문에 별도로 선언하지 않는다.
protected:
	/*--------------------------------------------------------------------------------------------
	-- virtual : 함수가 가상함수로 선언되면 상속받는 자식클래스에서 함수를 재정의해서 쓸수있다. 
	             가상함수 호출시 포인터 변수가 실제로 가리키는 객체를 참조하여 호출대상을 결정한다.
	-- override : 자식 클래스에서 선언되어 있는 가상함수(virtual함수)에 override 키워드를 붙여
	              부모 클래스에서 가상함수(virtual함수)를 재정의(overriding)한다.
	-- BeginPlay() : 런타임에서 최초 1번 실행한다. 
	-- Tick() : 런타임에서 매 프레임마다 1번 실행한다. 
	-- SetupPlayerInputComponent() : 언리얼 프로젝트 세팅에 정의된 플레이어 입력을 처리한다.
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

	//TakeDamage는 Actor에 정의된 TakeDamage 함수를 재정의하여 사용한다.
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	/*----------------------------------------------------------------------------------------------
	-- UPROPERTY / UFUNCTION 매크로 : 헤더의 속성값에 프로퍼티 매크로를 부여하여 에디터에서 값을 수정할 수 있게 만들거나, 
	   블루프린트에서 상속받아 사용할 때 읽고쓰게 할 수 있도록 설정할 수 있다. 

	-- EditAnywhere : 에디터에서 수정가능
	-- VisibleAnywhere : 에디터에서 표시
	-- BlueprintReadWrite : 블루프린트 상속시 Getter/Setter 가능
	-- BlueprintReadOnly : 블루프린트 상속시 Getter만 가능
	-- Category : 카테고리명을 지정하여 전시
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
