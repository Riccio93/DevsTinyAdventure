#include "ChangeAISpeed.h"
#include "EnemyCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GEPlatformerAIController.h"

UChangeAISpeed::UChangeAISpeed(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Change Speed");
	WalkSpeed = 250.f;
}

EBTNodeResult::Type UChangeAISpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGEPlatformerAIController* const AIController = Cast<AGEPlatformerAIController>(OwnerComp.GetAIOwner());
	if (AEnemyCharacter* const Enemy = Cast<AEnemyCharacter>(AIController->GetPawn()))
	{
		Enemy->FindComponentByClass<UFloatingPawnMovement>()->MaxSpeed = WalkSpeed;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
}

