#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UENUM()
enum class EAimType : uint8
{
	Third = 0, First, Max,
};

UCLASS()
class C_PORTFOLIO_API ACRifle : public AActor
{
	GENERATED_BODY()

public:
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	static ACRifle* Spawn(TSubclassOf<ACRifle> RifleClass, class ACharacter* InOwner);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* GrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* UngrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage_Play")
		float GrabMontageSpeed = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Montage_Play")
		float UngrabMontageSpeed = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		TSubclassOf<class UCAim> AimClasses[(int32)EAimType::Max];

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float PitchAngle = 0.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float LimitPitchAngle = 0.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class USoundWave* Sound;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* FlashParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UCUserWidget_Aim> AimWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UCUserWidget_AutoFire> AutoFireWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float AutoFireInterval = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float AimDistance = 3000.0f;

protected:
	UPROPERTY(BlueprintReadWrite)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }

public:
	void Equip();
	void Begin_Equip();
	void End_Equip();

public:
	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

public:
	void Begin_Aim();
	void End_Aim();
	bool IsAiming();

private:
	UFUNCTION()
		void Fire();

public:
	void Begin_Fire();
	void End_Fire();

	void Toggle_AutoFire();

private:
	bool bEquipping;
	bool bEquipped;
	bool bFiring;

	float CurrPitchAngle;

private:
	class UCUserWidget_Aim* AimWidget;
	class UCUserWidget_AutoFire* AutoFireWidget;

private:
	FTimerHandle AutoFireHandle;

private:
	UPROPERTY()
		class UCAim* Aims[(int32)EAimType::Max];
};
