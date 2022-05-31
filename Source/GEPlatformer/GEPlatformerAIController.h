#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionComponent* PerceptionComp;
	UPROPERTY(transient)
	class UAISenseConfig_Sight* SightConfig;

	void OnPossess(APawn* ControlledPawn) override;

	UFUNCTION()
	void OnSightUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);

	//Blackboard Keys IDs
	//int BBPatrolLocationID;
	//int BBPatrolPathIndexID;
};

