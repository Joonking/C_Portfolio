#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_AutoFire.generated.h"

UCLASS()
class C_PORTFOLIO_API UCUserWidget_AutoFire : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetOn() { return bOn; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void On_AutoFire();

	UFUNCTION(BlueprintImplementableEvent)
		void Off_AutoFire();

public:
	bool Toggle();

private:
	bool bOn;
};