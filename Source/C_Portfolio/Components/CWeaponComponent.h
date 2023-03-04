#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

//���� Ÿ�� Enum
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle, Pistol, Throwaway, Max
	//Rifle				: ����
	//Pistol			: ����
	//Thowaway		: ��ô��
};

//���Ⱑ ����ɶ� ȣ�� ���� ��������Ʈ
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
	//���� ���� Ÿ�� ��ȯ �Լ�
	UFUNCTION(BlueprintPure)
		FORCEINLINE EWeaponType GetType() { return Type; }

	//UnarmedMode ���� ��ȯ
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }

	//Rifle_1 Mode ���� ��ȯ
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRifleMode() { return Type == EWeaponType::Rifle; }

	//Pistol Mode ���� ��ȯ
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsPistolMode() { return Type == EWeaponType::Pistol; }

	//Throwaway Mode ���� ��ȯ
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsThrowawayMode() { return Type == EWeaponType::Throwaway; }

public:
	//���� Ÿ�� ���� �Լ���
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
		void SetRifleMode();

	UFUNCTION(BlueprintCallable)
		void SetPistolMode();

	UFUNCTION(BlueprintCallable)
		void SetThrowawayMode();

public:
	//�������Ʈ���� ȣ���� ��������Ʈ��
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
	//WeaponComponent�� ������ ����
	class ACharacter* OwnerCharacter;
	//���� ���� Ÿ���� ������ ����
	EWeaponType Type = EWeaponType::Max;   //Max�� Unarmed Ÿ��

	//������ �����
	class ACWeapon* Rifle;
	class ACWeapon* Pistol;
	class ACWeapon* Throwaway;

	//���� ������ ����
	class ACWeapon* CurrentWeapon;
};
