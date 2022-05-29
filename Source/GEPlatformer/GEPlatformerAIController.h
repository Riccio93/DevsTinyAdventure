#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GEPlatformerAIController.generated.h"

UCLASS()
class GEPLATFORMER_API AGEPlatformerAIController : public AAIController
{
	GENERATED_BODY()


public:

	AGEPlatformerAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(transient)
		class UBlackboardComponent* BlackboardComponent;

	void OnPossess(APawn* ControlledPawn) override;

	//Blackboard Keys IDs
	//int BBPatrolLocationID;
	//int BBPatrolPathIndexID;
};

