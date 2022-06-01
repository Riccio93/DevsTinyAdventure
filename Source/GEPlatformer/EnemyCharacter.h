#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DefaultPawn.h"
#include "EnemyCharacter.generated.h"

UCLASS(Abstract, Blueprintable)
class GEPLATFORMER_API AEnemyCharacter : public ADefaultPawn
{
	GENERATED_BODY()

		/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneComponent;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	int CoinsGivenToPlayer;

	bool bIsCapsuleOverlapping;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	//Collision functions
	UFUNCTION()
	void OnSphereOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
