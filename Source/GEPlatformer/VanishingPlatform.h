#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VanishingPlatform.generated.h"

UCLASS()
class GEPLATFORMER_API AVanishingPlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Platform, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Platform, meta = (AllowPrivateAccess = "true"))
	float DestroyTime;

	FVector OriginalLocation;
	FRotator OriginalRotation;
	
public:	
	
	AVanishingPlatform();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlatformFall();

	void RespawnPlatform();
};