#include "Characters/CPlayer.h"
#include "Global.h"
#include "Components/CMoveComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Weapons/CRifle.h"


ACPlayer::ACPlayer()
{
 	PrimaryActorTick.bCanEverTick = true;

	//SpringArm, Camera Component
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	//MoveComponent
	CHelpers::CreateActorComponent<UCMoveComponent>(this, &Move, "Move");
	//StateComponent
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	//StatusComponent
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	//WeaponComponent
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");

	//SkeletalMesh ����
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Military/Mesh/SK_Military_Rebel5.SK_Military_Rebel5'");
	GetMesh()->SetSkeletalMesh(mesh);

	//ĳ���� ��ġ, ���� ����
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//�ִϸ��̼� ���� ����
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Character/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);

	//SpringArm�� ��ġ ����
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	SpringArm->bEnableCameraLag = true;

	//�̵� ����
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400;

	//������ Ŭ���� ����
	CHelpers::GetClass<ACRifle>(&RifleClass, "Blueprint'/Game/Weapons/BP_Rifle_AR4.BP_Rifle_AR4_C'");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//��������Ʈ ����
	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

	Rifle = ACRifle::Spawn(RifleClass, this);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//����� �̺�Ʈ ���� ====================================================================
	PlayerInputComponent->BindAxis("MoveForward", Move, &UCMoveComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", Move, &UCMoveComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", Move, &UCMoveComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", Move, &UCMoveComponent::OnVerticlaLook);
	//=================================================================================

	//�Է� ���� �̺�Ʈ ���� ==================================================================
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, Move, &UCMoveComponent::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, Move, &UCMoveComponent::OffRun);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);
	PlayerInputComponent->BindAction("RifleTest", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::SetRifleMode);

	PlayerInputComponent->BindAction("SubAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnSubAction);
	PlayerInputComponent->BindAction("SubAction", EInputEvent::IE_Released, this, &ACPlayer::OffSubAction);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::OnAutoFire);
	//=================================================================================

}

//State Ÿ���� ����ɶ�, ��������Ʈ�� ���� ȣ��� �Լ�.
void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	//TODO: State Ÿ�Ժ� ȣ������ �Լ��� �����.
	switch (InNewType)
	{
	case EStateType::Hitted:
		break;  
	case EStateType::Dead:  
		break;
	}
}

void ACPlayer::OnRifle()
{
	Rifle->Equip();
}

bool ACPlayer::IsEquipped_Rifle()
{
	return Rifle->IsEquipped();
}

bool ACPlayer::IsAiming_Rifle()
{
	return Rifle->IsAiming();
}

void ACPlayer::Begin_Equip_Rifle()
{
	Rifle->Begin_Equip();
}

void ACPlayer::End_Equip_Rifle()
{
	Rifle->End_Equip();
}

void ACPlayer::Begin_Unequip_Rifle()
{
	Rifle->Begin_Unequip();
}

void ACPlayer::End_Unequip_Rifle()
{
	Rifle->End_Unequip();
}

void ACPlayer::OnSubAction()
{
	Rifle->Begin_Aim();
}

void ACPlayer::OffSubAction()
{
	Rifle->End_Aim();
}

void ACPlayer::OnFire()
{
	Rifle->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Rifle->End_Fire();
}

void ACPlayer::OnAutoFire()
{
	Rifle->Toggle_AutoFire();
}

