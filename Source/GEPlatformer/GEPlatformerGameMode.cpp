// Copyright Epic Games, Inc. All Rights Reserved.

#include "GEPlatformerGameMode.h"
#include "MainCharacter.h"
#include "InGameHUD.h"
#include "GEPlatformerPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AGEPlatformerGameMode::AGEPlatformerGameMode()
{
	//Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Set HUD class to our blueprinted HUD
	static ConstructorHelpers::FClassFinder<AInGameHUD> InGameHudBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_InGameHUD"));
	if (InGameHudBPClass.Class != NULL)
	{
		HUDClass = InGameHudBPClass.Class;
	}

	//Set PlayerController class to our blueprinted player controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_GEPlatformerPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	CoinsCount = 0;
	TotalCoinsCount = 100;
}

void AGEPlatformerGameMode::UpdateCoins(int Value)
{
	//DEBUG, GIVES 100 COINS
	CoinsCount += (Value * 100);

	//Update coins value on the HUD
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->UpdateCoinsCount(CoinsCount, TotalCoinsCount);
	}

	if(CoinsCount >= TotalCoinsCount)
	{
		if(InGameHUD)
		{
			InGameHUD->ShowGameOverScreen(true);
		}
	}
}

int AGEPlatformerGameMode::GetTotalCoinsCount()
{
	return TotalCoinsCount;
}

float AGEPlatformerGameMode::GetGameTime()
{
	GameTime = GetGameTimeSinceCreation();
	return GameTime;
}