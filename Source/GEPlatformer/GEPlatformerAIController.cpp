#include "GEPlatformerAIController.h"
#include "EnemyCharacter.h"
#include "MonsterEnemy.h"
#include "MainCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AGEPlatformerAIController::AGEPlatformerAIController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));

	//AIPerception
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight Config"));
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1525.f;
	SightConfig->PeripheralVisionAngleDegrees = 120.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AGEPlatformerAIController::OnSightUpdated(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	if (AMainCharacter* MC = Cast<AMainCharacter>(UpdatedActor))
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			//Timer??
			GetBlackboardComponent()->SetValueAsObject("EnemyActor", MC);
			UE_LOG(LogTemp, Warning, TEXT("Detecting!"));
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject("EnemyActor", nullptr);
			UE_LOG(LogTemp, Warning, TEXT("Not detecting!"));
		}		
	}	
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

		//Perception is only allowed when the enemy is a monster
		if(AMonsterEnemy* MonsterEnemy = Cast<AMonsterEnemy>(Enemy))
		{
			PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AGEPlatformerAIController::OnSightUpdated);
		}
	}
}