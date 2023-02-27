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
	//����� ���������� �Ű������� �־��ְ�, 
	//���ο��� ���� -���� ���̷��� -1�� ������.

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	//������ �޾����� ȣ������ ��������Ʈ
	if (OnDamaged.IsBound())
		OnDamaged.Broadcast();
}
