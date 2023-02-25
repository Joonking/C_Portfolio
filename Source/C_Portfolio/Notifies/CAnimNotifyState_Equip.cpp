#include "Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Weapons/IRifle.h"


FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	if (bUnequip)
	{
		rifle->Begin_Unequip_Rifle();

		return;
	}

	rifle->Begin_Equip_Rifle();
}


void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	if (bUnequip)
	{
		rifle->End_Unequip_Rifle();

		return;
	}

	rifle->End_Equip_Rifle();
}




