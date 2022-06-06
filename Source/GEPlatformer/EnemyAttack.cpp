#include "EnemyAttack.h"
//Components
#include "BehaviorTree/BlackboardComponent.h"
//My Classes
#include "GEPlatformerAIController.h"
#include "MainCharacter.h"
#include "MonsterEnemy.h"

UEnemyAttack::UEnemyAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Enemy Attack");
	AttackDamage = .25f;
}

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerComp.GetAIOwner());

	//Only monster enemies can attack the player
	if (AMonsterEnemy* const MonsterEnemy = Cast<AMonsterEnemy>(AIController->GetPawn()))
	{	
		MonsterEnemy->PlayAttacksMontage();
		//The player takes damage
		UObject* AttackedObject = AIController->BlackboardComponent->GetValueAsObject("EnemyActor");
		if (AMainCharacter* MC = Cast<AMainCharacter>(AttackedObject))
		{
			MC->PlayerTakeDamage(AttackDamage);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}	
}
