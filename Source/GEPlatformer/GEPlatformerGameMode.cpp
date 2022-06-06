#include "GEPlatformerGameMode.h"
#include "UObject/ConstructorHelpers.h"
//My Classes
#include "MainCharacter.h"
#include "InGameHUD.h"
#include "GEPlatformerPlayerController.h"

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
	TotalCoinsCount = 150;
	HealthValue = 1.f;
	MaxHealthValue = 1.f;
	HeartHealthRecover = .25f;
}

void AGEPlatformerGameMode::UpdateCoins(int Value)
{
	CoinsCount += (Value);

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

int AGEPlatformerGameMode::GetCoinsCount()
{
	return CoinsCount;
}

float AGEPlatformerGameMode::GetGameTime()
{
	GameTime = GetGameTimeSinceCreation();
	return GameTime;
}

void AGEPlatformerGameMode::UpdateHealth(float Value)
{
	HealthValue += Value;
	if(HealthValue > MaxHealthValue)
	{
		HealthValue = MaxHealthValue;
	}

	//Update health value on the HUD
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->UpdateHealth(HealthValue);
	}

	if (HealthValue <= 0)
	{
		if (InGameHUD)
		{
			InGameHUD->ShowGameOverScreen(false);			
		}
	}
}
