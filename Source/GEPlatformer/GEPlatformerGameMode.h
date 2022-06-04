// Copyright Epic Games, Inc. All Rights Reserved.

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

public:
	AGEPlatformerGameMode();
	void UpdateCoins(int Value);
	int GetTotalCoinsCount();
	float GetGameTime();
};



