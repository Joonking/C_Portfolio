#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class C_PORTFOLIO_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	//���� ������
	UPROPERTY(BlueprintReadWrite)
		class ACharacter* OwnerCharacter;

	//���� Aim Widget
	UPROPERTY(EditDefaultsOnly, Category = "AimWidget")
		TSubclassOf<class UCUserWidget_Aim> AimWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		class UAnimMontage* EquipMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		float EquipMontageSpeed = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		class UAnimMontage* UnEquipMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		float UnEquipMontageSpeed = 1;

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

public:
	//���� ������ ����
	FORCEINLINE bool IsEquipped() { return bEquipped; }

public: //Equip
	virtual void Equip();
	virtual void Begin_Equip();
	virtual void End_Equip();

public: //UnEquip
	virtual void UnEquip();
	virtual void Begin_UnEquip();
	virtual void End_UnEquip();


protected:
	bool bEquipping;
	bool bEquipped;
	bool bFiring;

private:
	class UCUserWidget_Aim* AimWidget;


};
