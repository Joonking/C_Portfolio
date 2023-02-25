#include "Weapons/CAim_Third.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

UCAim_Third::UCAim_Third()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Aim/Curve_Aim.Curve_Aim'");
}

void UCAim_Third::BeginPlay(ACharacter* InCharacter, ACRifle* InRifle)
{
	Super::BeginPlay(InCharacter, InRifle);

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);


	FOnTimelineFloat zoomDelegate;
	zoomDelegate.BindUFunction(this, "Zooming");

	Timeline.AddInterpFloat(Curve, zoomDelegate);
	Timeline.SetPlayRate(CurveSpeed);
}

void UCAim_Third::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

bool UCAim_Third::IsAvaliableZoom()
{
	Super::IsAvaliableZoom();

	return !!SpringArm && !!Camera;
}

void UCAim_Third::Begin_Aim()
{
	Super::Begin_Aim();

	CheckFalse(IsAvaliableZoom());
	CheckTrue(bAiming);

	bAiming = true;

	OriginAimData.TargetArmLength = SpringArm->TargetArmLength;
	OriginAimData.SocketOffset = SpringArm->SocketOffset;
	OriginAimData.bEnableCameraLag = SpringArm->bEnableCameraLag;

	SpringArm->TargetArmLength = AimData.TargetArmLength;
	SpringArm->SocketOffset = AimData.SocketOffset;
	SpringArm->bEnableCameraLag = AimData.bEnableCameraLag;

	//Camera->FieldOfView = 40;
	Timeline.PlayFromStart();
}

void UCAim_Third::End_Aim()
{
	Super::End_Aim();

	CheckFalse(IsAvaliableZoom());
	CheckFalse(bAiming);


	bAiming = false;

	SpringArm->TargetArmLength = OriginAimData.TargetArmLength;
	SpringArm->SocketOffset = OriginAimData.SocketOffset;
	SpringArm->bEnableCameraLag = OriginAimData.bEnableCameraLag;

	//Camera->FieldOfView = 90;
	Timeline.ReverseFromEnd();
}

void UCAim_Third::Zooming(float Output)
{
	Super::Zooming(Output);

	Camera->FieldOfView = Output;
}