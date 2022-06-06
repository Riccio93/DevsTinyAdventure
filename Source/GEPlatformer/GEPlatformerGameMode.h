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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int TotalCoinsCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Game", meta = (AllowPrivateAccess = "true"))
	float GameTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float HealthValue;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
		float HeartHealthRecover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
		float MaxHealthValue;

	AGEPlatformerGameMode();

	void UpdateCoins(int Value);
	
	int GetCoinsCount();

	int GetTotalCoinsCount();

	float GetGameTime();

	void UpdateHealth(float Value);
};



