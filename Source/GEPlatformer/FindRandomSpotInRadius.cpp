#include "FindRandomSpotInRadius.h"
//Components
#include "BehaviorTree/BlackboardComponent.h"
//My Classes
#include "GEPlatformerAIController.h"
#include "MonsterEnemy.h"
#include "NavigationSystem.h"

//Behavior Tree Task

UFindRandomSpotInRadius::UFindRandomSpotInRadius(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Spot In Radius");
	PatrolRadius = 200.f;
}

EBTNodeResult::Type UFindRandomSpotInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerBTComponent, uint8* NodeMemory)
{
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerBTComponent.GetAIOwner());

	//Patrolling in a random spot is only meant for monster enemies
	if (AMonsterEnemy* const MonsterEnemy = Cast<AMonsterEnemy>(AIController->GetPawn()))
	{
		FVector ActorLocation = MonsterEnemy->GetActorLocation();
		if(UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			//Gets the random point and writes it on the blackboard
			FVector PatrolLocation = NavSystem->GetRandomReachablePointInRadius(GetWorld(), ActorLocation, PatrolRadius);
			AIController->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", PatrolLocation);
		}
		else
		{
			FinishLatentTask(OwnerBTComponent, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
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
