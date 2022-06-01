#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "IncrementPatrolPathIndex.generated.h"

UCLASS()
class GEPLATFORMER_API UIncrementPatrolPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UIncrementPatrolPathIndex(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;		
};
