#include "EnemyCharacter.h"

//Components
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

//My classes
#include "MainCharacter.h"
#include "GEPlatformerGameMode.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	//Components setup
	GetCollisionComponent()->SetGenerateOverlapEvents(true);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnSphereOverlapBegin);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnSphereOverlapEnd);	
	bUseControllerRotationYaw = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComponent");
	BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnBoxOverlapBegin);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AttackDamage = .25f;
	CoinsGivenToPlayer = 5;
	bIsCapsuleOverlapping = false;
}

//Collision with the body of the enemy - The player takes damage on contact
void AEnemyCharacter::OnSphereOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = true;
		MainCharacter->PlayerTakeDamage(AttackDamage);
	}
}

void AEnemyCharacter::OnSphereOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = false;
	}
}

//Collision with the box on top of the enemy's head
void AEnemyCharacter::OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		//If the player is overlapping with both the box and the sphere collider, it won't die
		//(e.g. the player is just standing in the enemy's mesh)
		//So it only dies if the player only collides with the box
		if(!bIsCapsuleOverlapping)
		{
			this->Destroy();
			//The player auto-jumps
			MainCharacter->EnemyKilledJump();
			if(AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode()))
			{
				GEPGameMode->UpdateCoins(CoinsGivenToPlayer);
			}
		}		
	}
}

