#pragma once

#include "CoreMinimal.h"
#include "Weapons/CAim.h"
#include "Components/TimelineComponent.h"
#include "CAim_Third.generated.h"

USTRUCT()
struct FAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		float TargetArmLength = 150;

	UPROPERTY(EditDefaultsOnly)
		FVector SocketOffset = FVector(0, 50, 10);

	UPROPERTY(EditDefaultsOnly)
		bool bEnableCameraLag = false;
};

UCLASS(Blueprintable)
class C_PORTFOLIO_API UCAim_Third : public UCAim
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		FAimData AimData;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		float CurveSpeed = 200;

public:
	UCAim_Third();

	void BeginPlay(class ACharacter* InCharacter, class ACRifle* InRifle) override;
	void Tick(float DeltaTime) override;

	bool IsAvaliableZoom() override;

	void Begin_Aim() override;
	void End_Aim() override;

private:
	UFUNCTION()
		void Zooming(float Output) override;

private:
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	FAimData OriginAimData;

	FTimeline Timeline;
};
