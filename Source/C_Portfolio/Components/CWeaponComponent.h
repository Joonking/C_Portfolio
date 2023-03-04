#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

//무기 타입 Enum
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle, Pistol, Throwaway, Max
	//Rifle				: 소총
	//Pistol			: 권총
	//Thowaway		: 투척물
};

//무기가 변경될때 호출 해줄 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	//현재 무기 타입 반환 함수
	UFUNCTION(BlueprintPure)
		FORCEINLINE EWeaponType GetType() { return Type; }

	//UnarmedMode 인지 반환
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }

	//Rifle_1 Mode 인지 반환
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRifleMode() { return Type == EWeaponType::Rifle; }

	//Pistol Mode 인지 반환
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPistolMode() { return Type == EWeaponType::Pistol; }

	//Throwaway Mode 인지 반환
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsThrowawayMode() { return Type == EWeaponType::Throwaway; }

public:
	//무기 타입 변경 함수들
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
		void SetRifleMode();

	UFUNCTION(BlueprintCallable)
		void SetPistolMode();

	UFUNCTION(BlueprintCallable)
		void SetThrowawayMode();

public:
	//블루프린트에서 호출할 델리게이트들
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FWeaponTypeChanged OnWeaponTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACWeapon> RifleClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACWeapon> PistolClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACWeapon> ThrowawayClass;

private:
	void ChangeType(EWeaponType InType);
	void SetMode(EWeaponType InType);

private:
	//WeaponComponent의 소유자 변수
	class ACharacter* OwnerCharacter;
	//현재 무기 타입을 저장할 변수
	EWeaponType Type = EWeaponType::Max;   //Max가 Unarmed 타입

	//소유한 무기들
	class ACWeapon* Rifle;
	class ACWeapon* Pistol;
	class ACWeapon* Throwaway;

	//현재 장착한 무기
	class ACWeapon* CurrentWeapon;
};
