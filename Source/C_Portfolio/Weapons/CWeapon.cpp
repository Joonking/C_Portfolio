#include "Weapons/CWeapon.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/CUserWidget_Aim.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!!AimWidgetClass)
	{
		AimWidget = CreateWidget<UCUserWidget_Aim, APlayerController>
			(
				OwnerCharacter->GetController<APlayerController>(),
				AimWidgetClass
				);
		AimWidget->AddToViewport();
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
	}

}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACWeapon::Equip()
{
	CheckTrue(bEquipping);

	bEquipping = true;
	if (bEquipped)
	{
		UnEquip();

		return;
	}

	if(!!EquipMontage)
		OwnerCharacter->PlayAnimMontage(EquipMontage, EquipMontageSpeed);
}

void ACWeapon::Begin_Equip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
	bEquipped = true;

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	if(!!AimWidgetClass)
		AimWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACWeapon::End_Equip()
{
	bEquipping = false;
}

void ACWeapon::UnEquip()
{
	OwnerCharacter->PlayAnimMontage(UnEquipMontage, UnEquipMontageSpeed);
}

void ACWeapon::Begin_UnEquip()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	bEquipped = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (!!AimWidgetClass)
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACWeapon::End_UnEquip()
{
	bEquipping = false;
}

