// Copyright Epic Games, Inc. All Rights Reserved.

#include "GEPlatformerGameMode.h"
#include "GEPlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGEPlatformerGameMode::AGEPlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
