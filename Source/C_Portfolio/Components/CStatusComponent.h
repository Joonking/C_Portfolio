#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDamaged);

UCLASS(ClassGroup = (Custom))
class C_PORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
		float Health;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Delegate")
		FDamaged OnDamaged;

public:
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

public:
	void Damage(float InAmount);

private:
	class ACharacter* OwnerCharacter;

};
