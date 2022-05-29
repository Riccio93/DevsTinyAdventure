#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindPatrolPathLocation.generated.h"


UCLASS()
class GEPLATFORMER_API UFindPatrolPathLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindPatrolPathLocation(const FObjectInitializer& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;	
};
