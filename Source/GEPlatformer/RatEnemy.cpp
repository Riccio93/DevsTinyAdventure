#include "RatEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"


ARatEnemy::ARatEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent->InitBoxExtent(FVector(90.f, 90.f, 10.f));
	BoxComponent->AddRelativeLocation(FVector(0.f, 0.f, 125.f));

	SkeletalMeshComponent->AddWorldRotation(FRotator(0.f, -90.f, 0.f));
	SkeletalMeshComponent->AddRelativeLocation(FVector(0.f, 0.f, -90.f));

	//GetMovementComponent()->MaxSpeed = 600.f;
	
};

APatrolPath* ARatEnemy::GetPatrolPath()
{
	return PatrolPath;
}

int ARatEnemy::GetNumberOfPoints()
{
	return PatrolPath->NumberOfPoints();
}