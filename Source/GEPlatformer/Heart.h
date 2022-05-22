#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Heart.generated.h"

UCLASS()
class GEPLATFORMER_API AHeart : public APickup
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComponent;

public:
	// Sets default values for this actor's properties
	AHeart();
	
};
