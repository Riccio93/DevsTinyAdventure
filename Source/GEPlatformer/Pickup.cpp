#include "Pickup.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementcomponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/PointLightComponent.h"


// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("APickup::RotatingMovementComponent");
	RotatingMovementComponent->RotationRate = FRotator(.0f, .0f, 180.f);

	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("APickup::InterpToMovementComponent");
	InterpToMovementComponent->AddControlPointPosition(FVector(0.f, 0.f, 0.f), true);
	InterpToMovementComponent->AddControlPointPosition(FVector(0.f, 0.f, 40.f), true);
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpToMovementComponent->Duration = 0.7f;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("APickup::CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(22.f, 22.f);
	RootComponent = CapsuleComponent;
	//CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel1); //Pickup object channel (TODO: if unused remove from the project settings)
	
	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("APickup::SMesh");
	SMeshComponent->SetupAttachment(RootComponent);

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("APickup::PointLightComponent");
	PointLightComponent->SetIntensity(200.f);
	PointLightComponent->SetCastShadows(false);
	PointLightComponent->SetupAttachment(RootComponent);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
