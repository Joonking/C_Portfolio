#include "Weapons/CBullet.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"
#include "Components/DecalComponent.h"

ACBullet::ACBullet()
{
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Capsule);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	Capsule->SetRelativeRotation(FRotator(90, 0, 0));
	Capsule->SetCapsuleHalfHeight(50);
	Capsule->SetCapsuleRadius(2);
	Capsule->SetCollisionProfileName("BlockAllDynamic");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Weapons/Bullet/Sphere.Sphere'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(1, 0.025f, 0.05f));
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));

	Projectile->InitialSpeed = 2e+4f; //2 * 10 ^ 4
	Projectile->MaxSpeed = 2e+4f; //2 * 10 ^ 4
	Projectile->ProjectileGravityScale = 0;


	CHelpers::GetAsset<UMaterialInstanceConstant>(&Decal, "MaterialInstanceConstant'/Game/Weapons/Bullet/M_Decal_Inst.M_Decal_Inst'");
	CHelpers::GetAsset<UParticleSystem>(&Particle, "ParticleSystem'/Game/Weapons/Bullet/Particle/VFX_Impact_Default.VFX_Impact_Default'");
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentHit.AddDynamic(this, &ACBullet::OnHit);
}

void ACBullet::Shoot(const FVector& InDirection)
{
	Projectile->Velocity = InDirection * Projectile->InitialSpeed;
}

void ACBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FRotator rotation = Hit.ImpactNormal.Rotation();

	if (!!Decal)
	{
		UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5), Hit.ImpactPoint, rotation, 10);
		decal->SetFadeScreenSize(0);
	}

	if (!!Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Hit.ImpactPoint, rotation);
	}

	Destroy();
}