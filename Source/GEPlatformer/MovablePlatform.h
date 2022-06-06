#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovablePlatform.generated.h"

UCLASS()
class GEPLATFORMER_API AMovablePlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform, meta = (AllowPrivateAccess = "true"))
	class UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Platform, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SMeshComponent;
	
public:	
	AMovablePlatform();
};
