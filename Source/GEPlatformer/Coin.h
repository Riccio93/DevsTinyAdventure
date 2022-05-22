#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Coin.generated.h"

UCLASS()
class GEPLATFORMER_API ACoin : public APickup
{
	GENERATED_BODY()
	
		/*UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/

public:
	// Sets default values for this actor's properties
	ACoin();
};
