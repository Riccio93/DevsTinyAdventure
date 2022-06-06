#include "MainMenuGameMode.h"
#include "MainMenuPlayerController.h"
#include "UObject/ConstructorHelpers.h"
//My Classes
#include "GEPlatformerGameMode.h"
#include "MainMenuHUD.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	//Set HUD class to our blueprinted HUD
	static ConstructorHelpers::FClassFinder<AMainMenuHUD> MainMenuHudBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_MainMenuHUD"));
	if (MainMenuHudBPClass.Class != NULL)
	{
		HUDClass = MainMenuHudBPClass.Class;
	}
	
	//Sets the player controller so that we can use the mouse to select
	static ConstructorHelpers::FClassFinder<AMainMenuPlayerController> MainMenuPlayerControllerBPClass(TEXT("/Game/GEPlatformer/Blueprints/BP_MainMenuPlayerController"));
	if (MainMenuPlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = MainMenuPlayerControllerBPClass.Class;
	}
}
