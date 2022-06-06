#include "Coin.h"

//Components
#include "Components/InterpToMovementComponent.h"
#include "Components/PointLightComponent.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = false;

	//Components Setup
	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("ACoin::InterpToMovementComponent");
	InterpToMovementComponent->AddControlPointPosition(FVector(0.f, 0.f, 0.f), true);
	InterpToMovementComponent->AddControlPointPosition(FVector(0.f, 0.f, 40.f), true);
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpToMovementComponent->Duration = 0.7f;
	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ACoin::SMesh");
	SMeshComponent->SetupAttachment(RootComponent);
	PointLightComponent->SetLightColor(FColor(255, 229, 18));
}