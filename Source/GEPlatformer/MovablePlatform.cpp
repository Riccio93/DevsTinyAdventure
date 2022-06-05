#include "MovablePlatform.h"
#include "Components/InterpToMovementComponent.h"

AMovablePlatform::AMovablePlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovementComponent");
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpToMovementComponent->Duration = 1.f;

	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
	SMeshComponent->SetupAttachment(RootComponent);
}

