#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyAttack.generated.h"

UCLASS()
class GEPLATFORMER_API UEnemyAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UEnemyAttack(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
