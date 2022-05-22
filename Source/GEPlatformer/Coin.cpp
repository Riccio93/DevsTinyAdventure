#include "Coin.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"

//Set default values
ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = false;

	PointLightComponent->SetLightColor(FColor(255, 229, 18));
}