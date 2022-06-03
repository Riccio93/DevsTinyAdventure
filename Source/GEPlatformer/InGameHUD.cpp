#include "InGameHUD.h"

AInGameHUD::AInGameHUD() {}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(CoinsWidgetClass)
	{
		CoinsWidget = CreateWidget<UCoinsWidget>(GetWorld(), CoinsWidgetClass);
		if(CoinsWidget)
		{
			CoinsWidget->AddToViewport(1);
		}
	}

	if(GameStartWidgetClass)
	{
		GameStartWidget = CreateWidget<UGameStartWidget>(GetWorld(), GameStartWidgetClass);
		if(GameStartWidget)
		{
			GameStartWidget->AddToViewport(2);
		}
	}

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;

	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
	}

	//InputComponent->BindAction("Pause", IE_Pressed, this, &AInGameHUD::OpenPauseMenu);
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//Called by the Main Character at BeginPlay
void AInGameHUD::InitializeValues(int totalCoinsCount)
{
	UpdateCoinsCount(0, totalCoinsCount);
	UpdateHealth(.5f); //TODO: Set to 1 when testing is done
}

void AInGameHUD::UpdateCoinsCount(int Value, int Total)
{
	if(CoinsWidget)
	{
		CoinsWidget->UpdateCoinsCount(Value, Total);
	}
}

void AInGameHUD::UpdateHealth(float Value)
{
	if(CoinsWidget)
	{
		CoinsWidget->UpdateHealthBar(Value);
	}
}

void AInGameHUD::OpenPauseMenu()
{
	if (PauseMenuWidget)
	{
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
		PauseMenuWidget->AddToViewport(3);
	}
}
