#include "EnemyAttack.h"
#include "GEPlatformerAIController.h"
#include "MonsterEnemy.h"

UEnemyAttack::UEnemyAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Enemy Attack");
}

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerComp.GetAIOwner());

	//Only monster enemies attack the player
	if (AMonsterEnemy* const MonsterEnemy = Cast<AMonsterEnemy>(AIController->GetPawn()))
	{
		//MonsterEnemy->
	}



	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
