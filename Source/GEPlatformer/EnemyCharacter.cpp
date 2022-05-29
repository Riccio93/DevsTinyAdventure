#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

#include "MainCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCollisionComponent()->SetGenerateOverlapEvents(true);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnSphereOverlapBegin);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnSphereOverlapEnd);	

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComponent");
	BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnBoxOverlapBegin);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AttackDamage = .25f;
	CoinsGivenToPlayer = 5;
	bIsCapsuleOverlapping = false;
}

void AEnemyCharacter::OnSphereOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = true;
		MainCharacter->TakeDamage(AttackDamage);
	}
}

void AEnemyCharacter::OnSphereOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = false;
	}
}

void AEnemyCharacter::OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		if(!bIsCapsuleOverlapping)
		{
			this->Destroy();
			MainCharacter->EnemyKilledJump();
			MainCharacter->AddCoinsToCounter(CoinsGivenToPlayer);
		}		
	}
}

