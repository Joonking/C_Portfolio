#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAim.generated.h"

UCLASS(Abstract)
class C_PORTFOLIO_API UCAim : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsAiming() { return bAiming; }

public:
	UCAim();

public:
	virtual void BeginPlay(class ACharacter* InCharacter, class ACRifle* InRifle);
	virtual void Tick(float DeltaTime) { }

	virtual bool IsAvaliableZoom() { return false; }

	virtual void Begin_Aim() { }
	virtual void End_Aim() { }

protected:
	virtual void Zooming(float Output) { }

protected:
	class ACharacter* OwnerCharacter;
	class ACRifle* Rifle;

	bool bAiming;
};
