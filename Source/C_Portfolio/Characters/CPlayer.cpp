#include "Characters/CPlayer.h"
#include "Global.h"
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

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400;

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Military/Mesh/SK_Military_Rebel5.SK_Military_Rebel5'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Character/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	SpringArm->bEnableCameraLag = true;


	CHelpers::GetClass<ACRifle>(&RifleClass, "Blueprint'/Game/Weapons/BP_Rifle_AR4.BP_Rifle_AR4_C'");

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	Rifle = ACRifle::Spawn(RifleClass, this);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("SubAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnSubAction);
	PlayerInputComponent->BindAction("SubAction", EInputEvent::IE_Released, this, &ACPlayer::OffSubAction);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);


}


void ACPlayer::OnMoveForward(float InAxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxisValue);
}

void ACPlayer::OnMoveRight(float InAxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxisValue);
}

void ACPlayer::OnVerticalLook(float InAxisValue)
{
	AddControllerPitchInput(InAxisValue);
}

void ACPlayer::OnHorizontalLook(float InAxisValue)
{
	AddControllerYawInput(InAxisValue);
}

void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
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



