#include "Coin.h"
#include "Components/CapsuleComponent.h"

//Set default values
ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}

void ACoin::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap begin function called");
	this->Destroy();
}