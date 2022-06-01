#include "MovablePlatform.h"
#include "Components/InterpToMovementComponent.h"

// Sets default values
AMovablePlatform::AMovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovementComponent");
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	InterpToMovementComponent->Duration = 1.f;

	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
	SMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

