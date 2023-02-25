#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/IRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Owner);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	//플레이어의 속도를 구해서 Speed에 넣어주기
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());

	IIRifle* rifle = Cast<IIRifle>(Owner);
	if (!!rifle)
	{
		bEquipped = rifle->IsEquipped_Rifle();
		//bAiming = rifle->IsAiming_Rifle();

		//if (bEquipped)
		//	forward = OwnerCharacter->GetActorRotation();
	}


}
