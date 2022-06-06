#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MonsterEnemy.generated.h"

UCLASS()
class GEPLATFORMER_API AMonsterEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AttackMontage;

	float OriginalZCoord;

public:
	AMonsterEnemy();	

	void BeginPlay() override;

	void Tick(float DeltaSeconds);

	float PlayAttacksMontage();
};
