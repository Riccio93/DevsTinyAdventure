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

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(transient)
	class UAISenseConfig_Sight* SightConfig;

	AGEPlatformerAIController(const FObjectInitializer& ObjectInitializer);	

	void OnPossess(APawn* ControlledPawn) override;

	UFUNCTION()
	void OnSightUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);
};

