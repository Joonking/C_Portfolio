#include "Weapons/CRifle.h"
#include "Global.h"
#include "CBullet.h"
//#include "CUserWidget_AutoFire.h"
#include "CAim.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundWave.h"
#include "Particles/ParticleSystem.h"


ACRifle::ACRifle()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapons/Rifle/Meshes/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	CHelpers::GetAsset<UAnimMontage>(&GrabMontage, "AnimMontage'/Game/Character/Montages/Rifle/Equip/Rifle_Equip_Montage.Rifle_Equip_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&UngrabMontage, "AnimMontage'/Game/Character/Montages/Rifle/Equip/Rifle_UnEquip_Montage.Rifle_UnEquip_Montage'");

	CHelpers::GetClass<UCAim>(&AimClasses[(int32)EAimType::Third], "Blueprint'/Game/Aim/BP_Aim_Third.BP_Aim_Third_C'");

	CHelpers::GetClass<ACBullet>(&BulletClass, "Blueprint'/Game/Weapons/Bullet/BP_Bullet.BP_Bullet_C'");
	CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/CameraShake/BP_Fire.BP_Fire_C'");

	CHelpers::GetAsset<USoundWave>(&Sound, "SoundWave'/Game/Sound/Shoot/S_RifleShoot.S_RifleShoot'");

	CHelpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Weapons/Bullet/Particle/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Weapons/Bullet/Particle/VFX_Eject_bullet.VFX_Eject_bullet'");

}

ACRifle* ACRifle::Spawn(TSubclassOf<ACRifle> RifleClass, ACharacter* InOwner)
{
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InOwner->GetWorld()->SpawnActor<ACRifle>(RifleClass, params);
}


void ACRifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),HolsterSocket);

	Aims[(int32)EAimType::Third] = NewObject<UCAim>(this, AimClasses[(int32)EAimType::Third]);
	Aims[(int32)EAimType::Third]->BeginPlay(OwnerCharacter, this);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!!Aims[(int32)EAimType::Third])
		Aims[(int32)EAimType::Third]->Tick(DeltaTime);
}


void ACRifle::Equip()
{
	CheckTrue(bEquipping);

	bEquipping = true;
	if (bEquipped)
	{
		Unequip();

		return;
	}

	OwnerCharacter->PlayAnimMontage(GrabMontage, GrabMontageSpeed);
}

void ACRifle::Begin_Equip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
	bEquipped = true;

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	//AutoFireWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACRifle::End_Equip()
{
	bEquipping = false;
}

void ACRifle::Unequip()
{
	OwnerCharacter->PlayAnimMontage(UngrabMontage, UngrabMontageSpeed);
}

void ACRifle::Begin_Unequip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	bEquipped = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	//AutoFireWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACRifle::End_Unequip()
{
	bEquipping = false;
}

void ACRifle::Begin_Aim()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	CheckNull(Aims[(int32)EAimType::Third]);

	Aims[(int32)EAimType::Third]->Begin_Aim();
}

void ACRifle::End_Aim()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	CheckNull(Aims[(int32)EAimType::Third]);

	Aims[(int32)EAimType::Third]->End_Aim();
}

bool ACRifle::IsAiming()
{
	bool b = false;

	if (!!Aims[(int32)EAimType::Third])
		b |= Aims[(int32)EAimType::Third]->IsAiming();

	return b;
}


void ACRifle::Fire()
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	FVector direction = camera->GetForwardVector();
	direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(direction, PitchAngle);


	FTransform transform = camera->GetComponentToWorld();
	FVector start = transform.GetLocation() + direction;
	FVector end = transform.GetLocation() + direction * AimDistance;

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, true, 5);


	FVector muzzleLocation = Mesh->GetSocketLocation("MuzzleFlash");

	if (!!CameraShakeClass)
		OwnerCharacter->GetController<APlayerController>()->PlayerCameraManager->StartCameraShake(CameraShakeClass);

	if (!!Sound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, muzzleLocation);

	if (!!FlashParticle)
		UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "MuzzleFlash");

	if (!!EjectParticle)
		UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet");

	//Pitch Angle
	{
		CurrPitchAngle -= PitchAngle * GetWorld()->GetDeltaSeconds();

		if (CurrPitchAngle > -LimitPitchAngle)
			OwnerCharacter->AddControllerPitchInput(CurrPitchAngle);
	}

	//Spawn Bullet
	{
		FVector spawnLocation = muzzleLocation + direction * 50;

		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletClass, spawnLocation, direction.Rotation());
		bullet->Shoot(direction);
	}
}

void ACRifle::Begin_Fire()
{
	CheckTrue(bEquipping);
	CheckFalse(bEquipped);
	CheckTrue(bFiring);

	bFiring = true;
	CurrPitchAngle = 0;

	/*if (AutoFireWidget->GetOn())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &ACRifle::Fire, AutoFireInterval, true);

		return;
	}*/

	Fire();
}

void ACRifle::End_Fire()
{
	//if (GetWorld()->GetTimerManager().IsTimerActive(AutoFireHandle))
	//	GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);

	bFiring = false;
}