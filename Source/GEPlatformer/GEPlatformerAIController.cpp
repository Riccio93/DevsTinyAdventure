#include "GEPlatformerAIController.h"
#include "EnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AGEPlatformerAIController::AGEPlatformerAIController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
}

void AGEPlatformerAIController::OnPossess(APawn* ControlledPawn)
{

	Super::OnPossess(ControlledPawn);

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(ControlledPawn);
	if (Enemy != nullptr && Enemy->BehaviorTree != nullptr)
	{
		BlackboardComponent->InitializeBlackboard(*Enemy->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Enemy->BehaviorTree);

		//Set Blackboard keys ID
		/*BBPatrolLocationID = BlackboardComponent->GetKeyID("PatrolLocation");
		BBPatrolPathIndexID = BlackboardComponent->GetKeyID("PatrolPathIndex");*/
	}
}