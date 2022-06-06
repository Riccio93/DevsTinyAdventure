#include "InGameHUD.h"

AInGameHUD::AInGameHUD() {}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

//Creates all the widgets and adds to the viewport the ones present at the start
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

	//Shows the mouse cursor to navigate the buttons screen
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->SetPause(true);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
	}

	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);
	}
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//Called by the Main Character at BeginPlay
void AInGameHUD::InitializeValues(int totalCoinsCount)
{
	UpdateCoinsCount(0, totalCoinsCount);
	UpdateHealth(1.f);
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
	if (PauseMenuWidget && !GameStartWidget->IsInViewport())
	{
		//Shows the mouse cursor to navigate the pause screen
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->SetPause(true);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		PauseMenuWidget->AddToViewport(3);
	}
}

void AInGameHUD::ShowGameOverScreen(bool bIsGameWon)
{
	if(GameOverWidget)
	{
		//Shows the mouse cursor to navigate the game over screen
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->SetPause(true);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GameOverWidget->InitializeWidgetElements(bIsGameWon);
		GameOverWidget->AddToViewport(4);		
	}
}