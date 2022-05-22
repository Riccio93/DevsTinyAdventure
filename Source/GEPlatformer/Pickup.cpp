#include "Pickup.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementcomponent.h"
#include "Components/PointLightComponent.h"


// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("APickup::RotatingMovementComponent");
	RotatingMovementComponent->RotationRate = FRotator(.0f, .0f, 180.f);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("APickup::CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(22.f, 22.f);
	RootComponent = CapsuleComponent;
	//CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel1); //Pickup object channel (TODO: if unused remove from the project settings)

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("APickup::PointLightComponent");
	PointLightComponent->SetIntensity(200.f);
	PointLightComponent->SetCastShadows(false);
	PointLightComponent->SetupAttachment(RootComponent);
}
