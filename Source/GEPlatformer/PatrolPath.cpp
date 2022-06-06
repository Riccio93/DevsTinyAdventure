#include "PatrolPath.h"

APatrolPath::APatrolPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

FVector APatrolPath::getPatrolPoint(int const index) const
{
	return PatrolPoints[index];
}

int APatrolPath::NumberOfPoints() const
{
	return PatrolPoints.Num();
}

