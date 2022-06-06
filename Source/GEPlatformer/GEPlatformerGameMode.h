#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GEPlatformerGameMode.generated.h"

UCLASS(minimalapi)
class AGEPlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int CoinsCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int TotalCoinsCount;

	UPROPERTY(VisibleAnywhere, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float GameTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float HealthValue;

public:
	AGEPlatformerGameMode();

	void UpdateCoins(int Value);

	int GetCoinsCount();

	int GetTotalCoinsCount();

	float GetGameTime();

	void UpdateHealth(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float HeartHealthRecover;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float MaxHealthValue;
};



