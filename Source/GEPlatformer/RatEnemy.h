#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "PatrolPath.h"
#include "RatEnemy.generated.h"

UCLASS()
class GEPLATFORMER_API ARatEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundWave* CrabWalkingSoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundAttenuation* SoundAttenuation;
	
public:
	ARatEnemy();

	void BeginPlay() override;
	APatrolPath* GetPatrolPath();
	int GetNumberOfPoints();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;
};
