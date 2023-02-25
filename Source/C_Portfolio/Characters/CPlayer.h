#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class C_PORTFOLIO_API ACPlayer
	: public ACharacter
	, public IIRifle
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Rifle")
		TSubclassOf<class ACRifle> RifleClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxisValue);
	void OnMoveRight(float InAxisValue);
	void OnVerticalLook(float InAxisValue);
	void OnHorizontalLook(float InAxisValue);

public:
	void OnRun();
	void OffRun();

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


private:
	class ACRifle* Rifle;


};
