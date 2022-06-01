#include "IncrementPatrolPathIndex.h"
#include "GEPlatformerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RatEnemy.h"

UIncrementPatrolPathIndex::UIncrementPatrolPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Patrol Path Index");
}

EBTNodeResult::Type UIncrementPatrolPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the AI controller
	AGEPlatformerAIController* const Controller = Cast<AGEPlatformerAIController>(OwnerComp.GetAIOwner());

	ARatEnemy* const Enemy = Cast<ARatEnemy>(Controller->GetPawn());

	int const NumberOfPoints = Enemy->GetNumberOfPoints();

	int index = Controller->BlackboardComponent->GetValueAsInt("PatrolPathIndex");

	if(index == NumberOfPoints - 1)
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
