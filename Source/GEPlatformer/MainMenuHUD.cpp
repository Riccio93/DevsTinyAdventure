#include "MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD() {}

void AMainMenuHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}