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
	// Sets default values for this actor's properties
	AMovablePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
