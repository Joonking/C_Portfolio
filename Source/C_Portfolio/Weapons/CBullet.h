#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class C_PORTFOLIO_API ACBullet : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		class UMaterialInstanceConstant* Decal;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		class UParticleSystem* Particle;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:
	ACBullet();

	void Shoot(const FVector& InDirection);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
