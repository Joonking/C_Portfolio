#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRifle.generated.h"

UINTERFACE(MinimalAPI)
class UIRifle : public UInterface
{
	GENERATED_BODY()
};

class C_PORTFOLIO_API IIRifle
{
	GENERATED_BODY()

public:
	virtual bool IsEquipped_Rifle() = 0;
	virtual bool IsAiming_Rifle() = 0;

	virtual void Begin_Equip_Rifle() = 0;
	virtual void End_Equip_Rifle() = 0;

	virtual void Begin_Unequip_Rifle() = 0;
	virtual void End_Unequip_Rifle() = 0;


};
