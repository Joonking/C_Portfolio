#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class C_PORTFOLIO_API ACPlayer : public ACharacter
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void OnMoveForward(float InAxisValue);
	void OnMoveRight(float InAxisValue);
	void OnVerticalLook(float InAxisValue);
	void OnHorizontalLook(float InAxisValue);

};
