#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class GEPLATFORMER_API APickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup , meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup,  meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLightComponent;

public:	
	APickup();
};
