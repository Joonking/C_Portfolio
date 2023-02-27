#include "Components/CStatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Health = MaxHealth;
}

void UCStatusComponent::Damage(float InAmount)
{
	Health += (InAmount * -1.0f);
	//양수의 데미지값을 매개변수로 넣어주고, 
	//내부에서 뺄때 -값을 붙이려고 -1을 곱해줌.

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	//데미지 받았을때 호출해줄 델리게이트
	if (OnDamaged.IsBound())
		OnDamaged.Broadcast();
}
