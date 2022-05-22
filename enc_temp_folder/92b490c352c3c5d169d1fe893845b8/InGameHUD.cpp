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
			CoinsWidget->AddToViewport();
		}
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
