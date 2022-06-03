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
}
