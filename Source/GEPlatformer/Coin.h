#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Coin.generated.h"

UCLASS()
class GEPLATFORMER_API ACoin : public APickup
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	class UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SMeshComponent;
	
public:
	ACoin();
};
