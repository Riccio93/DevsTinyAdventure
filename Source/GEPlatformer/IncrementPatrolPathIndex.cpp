#include "IncrementPatrolPathIndex.h"
//Components
#include "BehaviorTree/BlackboardComponent.h"
//My Classes
#include "RatEnemy.h"
#include "GEPlatformerAIController.h"

//Behavior Tree Task

UIncrementPatrolPathIndex::UIncrementPatrolPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Patrol Path Index");
}

EBTNodeResult::Type UIncrementPatrolPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGEPlatformerAIController* const Controller = Cast<AGEPlatformerAIController>(OwnerComp.GetAIOwner());

	//Only crab enemies use patrol paths
	if(ARatEnemy* const Enemy = Cast<ARatEnemy>(Controller->GetPawn()))
	{
		int const NumberOfPoints = Enemy->GetNumberOfPoints();
		int index = Controller->BlackboardComponent->GetValueAsInt("PatrolPathIndex");
		//Compute the next index to go to and write it back on the blackboard
		if (index == NumberOfPoints - 1)
		{
			index = 0;
		}
		else
		{
			index++;
		}
		Controller->BlackboardComponent->SetValueAsInt("PatrolPathIndex", index);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}	
}
