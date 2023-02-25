#include "Weapons/CRifle.h"
#include "Global.h"
//#include "CBullet.h"
//#include "CUserWidget_AutoFire.h"
//#include "CAim.h"
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
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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