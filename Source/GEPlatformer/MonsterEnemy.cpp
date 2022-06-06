#include "MonsterEnemy.h"
#include "Components/BoxComponent.h"

AMonsterEnemy::AMonsterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Setup
	BoxComponent->InitBoxExtent(FVector(24.f, 24.f, 4.f));
	BoxComponent->AddRelativeLocation(FVector(0.f, 0.f, 40.f));
	SkeletalMeshComponent->AddRelativeLocation(FVector(0.f, 0.f, -25.f));
}

void AMonsterEnemy::BeginPlay()
{
	Super::BeginPlay();
	OriginalZCoord = GetActorLocation().Z;
}

void AMonsterEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Without this fix, if the player jumps the enemy follows it in the air.
	//This way the monster never changes its Z coordinate
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, OriginalZCoord));
}

//Plays the attack animation montage
float AMonsterEnemy::PlayAttacksMontage()
{
	UAnimInstance* AnimInstance = (SkeletalMeshComponent) ? SkeletalMeshComponent->GetAnimInstance() : nullptr;
	if (AttackMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AttackMontage, 1.f);
		if (Duration > 0.f)
		{
			return Duration;
		}
	}
	return 0.f;
}
