#include "CoinsWidget.h"

UCoinsWidget::UCoinsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCoinsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCoinsWidget::UpdateCoinsCount(int Value, int Total)
{
	if(CoinsCountText)
	{
		CoinsCountText->SetText(FText::FromString(FString::FromInt(Value) + " / " + FString::FromInt(Total)));
		if(CoinObtainedAnimation)
		{
			PlayAnimation(CoinObtainedAnimation, .0f, 1, EUMGSequencePlayMode::Forward, 4.f);
		}
	}
}

void UCoinsWidget::UpdateHealthBar(float Value)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(Value);
	}
}
