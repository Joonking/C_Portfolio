#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/IRifle.h"
#include "Math/UnrealMathUtility.h"

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

	FRotator current = FRotator(Pitch, 0, 0);

	FRotator A = Owner->GetControlRotation();
	FRotator B = Owner->GetActorRotation();
	FRotator target = UKismetMathLibrary::NormalizedDeltaRotator(A, B);

	Pitch = UKismetMathLibrary::RInterpTo(current, target, DeltaSeconds, 0).Pitch;
	Pitch = UKismetMathLibrary::ClampAngle(Pitch, -90, 90);


	IIRifle* rifle = Cast<IIRifle>(Owner);

	FRotator forward = Owner->GetControlRotation();
	if (!!rifle)
	{
		bEquipped = rifle->IsEquipped_Rifle();
		bAiming = rifle->IsAiming_Rifle();

		if (bEquipped)
			forward = Owner->GetActorRotation();
	}

	float tempDirection = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());

	if (FMath::IsNearlyEqual(tempDirection, 0, 20))
		Direction = 0;
	else
	{
		if (FMath::IsNearlyEqual(tempDirection, 180, 30))
			Direction = -180;
		else
			Direction = tempDirection;
	}


}
