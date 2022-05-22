#include "InGameHUD.h"

AInGameHUD::AInGameHUD()
{

}

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

void AInGameHUD::UpdateCoinsCount(int Value, int Total)
{
	if(CoinsWidget)
	{
		CoinsWidget->UpdateCoinsCount(Value, Total);
	}
}

//void AInGameHUD::ResetCoinsCount()
//{
//	if(CoinsWidget)
//	{
//		CoinsWidget->ResetCoins();
//	}
//}
