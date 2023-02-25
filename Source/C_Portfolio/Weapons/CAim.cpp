#include "Weapons/CAim.h"
#include "Global.h"

UCAim::UCAim()
{

}

void UCAim::BeginPlay(ACharacter* InCharacter, ACRifle* InRifle)
{
	OwnerCharacter = InCharacter;
	Rifle = InRifle;
}
