#include "Notifies/CAnimNotify_Fire.h"
#include "Global.h"
#include "Weapons/IRifle.h"

FString UCAnimNotify_Fire::GetNotifyName_Implementation() const
{
	return "Fire";
}

void UCAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifle);

	//rifle->Fire_Rifle();
}
