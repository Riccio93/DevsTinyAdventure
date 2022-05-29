#include "FindPatrolPathLocation.h"
#include "GEPlatformerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"
#include "RatEnemy.h"

UFindPatrolPathLocation::UFindPatrolPathLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Find Patrol Path Location");
}

EBTNodeResult::Type UFindPatrolPathLocation::ExecuteTask(UBehaviorTreeComponent& OwnerBTComponent, uint8* NodeMemory)
{
	//Get the AI Controller and the current Patrol Path index from the blackboard
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerBTComponent.GetAIOwner());
	int const PathPatrolIndex = AIController->BlackboardComponent->GetValueAsInt("PatrolPathIndex");

	//The patrolling is only possible for rat enemies
	if(ARatEnemy* const RatEnemy = Cast<ARatEnemy>(AIController->GetPawn()))
	{
		//Use the index to get the current patrol path location, transform to global coordinates and write it on the blackboard
		FVector const NextPatrolPathLocation = RatEnemy->GetPatrolPath()->getPatrolPoint(PathPatrolIndex);
		FVector const GlobalLocation = RatEnemy->GetPatrolPath()->GetActorTransform().TransformPosition(NextPatrolPathLocation);
		AIController->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", GlobalLocation);

		FinishLatentTask(OwnerBTComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerBTComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}	
}
