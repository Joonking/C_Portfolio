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

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }

public:
	static ACRifle* Spawn(TSubclassOf<ACRifle> RifleClass, class ACharacter* InOwner);

public:	
	ACRifle();

public:
	void Equip();
	void Begin_Equip();
	void End_Equip();

private:
	void Unequip();
public:
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aim();
	void End_Aim();

	bool IsAiming();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	class ACharacter* OwnerCharacter;

private:
	bool bEquipping;
	bool bEquipped;
	bool bFiring;

	float CurrPitchAngle;

private:
	UPROPERTY()
		class UCAim* Aims[(int32)EAimType::Max];
};
