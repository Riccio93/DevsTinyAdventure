#include "Pickup.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementcomponent.h"
#include "Components/PointLightComponent.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	//Components Setup
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("APickup::RotatingMovementComponent");
	RotatingMovementComponent->RotationRate = FRotator(.0f, .0f, 180.f);
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("APickup::CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(22.f, 22.f);
	RootComponent = CapsuleComponent;
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("APickup::PointLightComponent");
	PointLightComponent->SetIntensity(200.f);
	PointLightComponent->SetCastShadows(false);
	PointLightComponent->SetupAttachment(RootComponent);
}
