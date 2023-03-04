#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeapon.h"

UCWeaponComponent::UCWeaponComponent()
{

}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;

	if(!!RifleClass)
	{
		Rifle = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(RifleClass, params);
	}

	if(!!PistolClass)
	{
		Pistol = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(RifleClass, params);
	}

	if(!!ThrowawayClass)
	{
		Throwaway = OwnerCharacter->GetWorld()->SpawnActor<ACWeapon>(RifleClass, params);
	}
	
}

void UCWeaponComponent::SetUnarmedMode()
{
	CheckNull(CurrentWeapon);
	CurrentWeapon->UnEquip();
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetRifleMode()
{
	SetMode(EWeaponType::Rifle);
}


void UCWeaponComponent::SetPistolMode()
{
	SetMode(EWeaponType::Pistol);
}

void UCWeaponComponent::SetThrowawayMode()
{
	SetMode(EWeaponType::Throwaway);
}

//무기 타입 변경 함수
void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, Type);
}

//무기 모드 변경 함수
void UCWeaponComponent::SetMode(EWeaponType InType)
{
	//현재 무기랑 바꿀 무기가 같을때(무기해제)
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false) //무기 장착 중 이라면
	{
		CurrentWeapon->UnEquip();
	}

	switch (InType)
	{
	case EWeaponType::Rifle:
		CheckNull(Rifle);
		CurrentWeapon = Rifle;
		break;
	case EWeaponType::Pistol:
		CheckNull(Pistol);
		CurrentWeapon = Pistol;
		break;
	case EWeaponType::Throwaway:
		CheckNull(Throwaway);
		CurrentWeapon = Throwaway;
		break;
	}
	CurrentWeapon->Equip();
	ChangeType(InType);

}


