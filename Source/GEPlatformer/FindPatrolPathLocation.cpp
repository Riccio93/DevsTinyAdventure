#include "FindPatrolPathLocation.h"
//Components
#include "BehaviorTree/BlackboardComponent.h"
//My Classes
#include "GEPlatformerAIController.h"
#include "EnemyCharacter.h"
#include "RatEnemy.h"

//Behavior Tree Task

UFindPatrolPathLocation::UFindPatrolPathLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Find Patrol Path Location");
}

EBTNodeResult::Type UFindPatrolPathLocation::ExecuteTask(UBehaviorTreeComponent& OwnerBTComponent, uint8* NodeMemory)
{
	//Get the AI Controller and the current Patrol Path index from the blackboard
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerBTComponent.GetAIOwner());
	int const PathPatrolIndex = AIController->BlackboardComponent->GetValueAsInt("PatrolPathIndex");

	//The patrolling on a path is only meant for rat enemies
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
