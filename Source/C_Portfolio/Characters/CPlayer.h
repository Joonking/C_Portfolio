#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Weapons/IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class C_PORTFOLIO_API ACPlayer
	: public ACharacter
	, public IIRifle
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCMoveComponent* Move;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
		class UCStatusComponent* Status;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Rifle")
		TSubclassOf<class ACRifle> RifleClass;

private:
	//State 타입이 변경될때, 델리게이트에 의해 호출될 함수.
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public:
	void OnRifle();

public:
	virtual bool IsEquipped_Rifle() override;
	virtual bool IsAiming_Rifle() override;

	virtual void Begin_Equip_Rifle() override;
	virtual void End_Equip_Rifle() override;
	virtual void Begin_Unequip_Rifle() override;
	virtual void End_Unequip_Rifle() override;

public:
	void OnSubAction();
	void OffSubAction();

public:
	void OnFire();
	void OffFire();

	void OnAutoFire();

private:
	class ACRifle* Rifle;


};
