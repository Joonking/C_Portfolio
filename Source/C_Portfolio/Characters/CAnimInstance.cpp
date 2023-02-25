#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

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

	//�÷��̾��� �ӵ��� ���ؼ� Speed�� �־��ֱ�
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetControlRotation());

}
