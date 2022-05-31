#include "FindRandomSpotInRadius.h"
#include "GEPlatformerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterEnemy.h"
#include "NavigationSystem.h"

UFindRandomSpotInRadius::UFindRandomSpotInRadius(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Spot In Radius");
	PatrolRadius = 200.f;
}

EBTNodeResult::Type UFindRandomSpotInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerBTComponent, uint8* NodeMemory)
{
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerBTComponent.GetAIOwner());

	//Patrolling in a random spot is only possible for monster enemies
	if (AMonsterEnemy* const MonsterEnemy = Cast<AMonsterEnemy>(AIController->GetPawn()))
	{
		FVector ActorLocation = MonsterEnemy->GetActorLocation();
		if(UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FVector PatrolLocation = NavSystem->GetRandomReachablePointInRadius(GetWorld(), ActorLocation, PatrolRadius);
			//FVector PatrolLocation = NavSystem->GetRandomPointInNavigableRadius(GetWorld(), ActorLocation, PatrolRadius);
			AIController->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", PatrolLocation);
		}
		FinishLatentTask(OwnerBTComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerBTComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
}
