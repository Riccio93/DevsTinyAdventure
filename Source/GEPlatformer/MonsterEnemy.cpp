#include "MonsterEnemy.h"
#include "Components/BoxComponent.h"

AMonsterEnemy::AMonsterEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent->InitBoxExtent(FVector(24.f, 24.f, 4.f));
	BoxComponent->AddRelativeLocation(FVector(0.f, 0.f, 40.f));

	//SkeletalMeshComponent->AddWorldRotation(FRotator(0.f, -90.f, 0.f));
	SkeletalMeshComponent->AddRelativeLocation(FVector(0.f, 0.f, -25.f));
}

void AMonsterEnemy::Attack()
{
	//PlayMontage()
}

void Tick(float DeltaSeconds)
{

}
