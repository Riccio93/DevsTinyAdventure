#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "PatrolPath.h"
#include "RatEnemy.generated.h"

UCLASS()
class GEPLATFORMER_API ARatEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AAIController> ControllerClass;*/
	
public:
	ARatEnemy();

	APatrolPath* GetPatrolPath();
	int GetNumberOfPoints();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;
};
