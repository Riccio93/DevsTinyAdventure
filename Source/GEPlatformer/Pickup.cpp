#include "Pickup.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementcomponent.h"
#include "Components/InterpToMovementComponent.h"


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

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("APickup::CapsuleComponent");
	CapsuleComponent->InitCapsuleSize(22.f, 22.f);
	RootComponent = CapsuleComponent;
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	//CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &APickup::OnOverlapEnd);
	
	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("APickup::SMesh");
	SMeshComponent->SetupAttachment(RootComponent);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	K2_DestroyActor();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap begin function called");
}

//void APickup::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	K2_DestroyActor();
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap end function called");
//}
