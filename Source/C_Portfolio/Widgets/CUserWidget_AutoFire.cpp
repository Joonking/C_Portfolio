#include "Widgets/CUserWidget_AutoFire.h"
#include "Global.h"

bool UCUserWidget_AutoFire::Toggle()
{
	bOn = !bOn;
	bOn ? On_AutoFire() : Off_AutoFire();

	return bOn;
}
