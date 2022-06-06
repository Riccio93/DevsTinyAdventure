#include "CoinsWidget.h"

UCoinsWidget::UCoinsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{}

void UCoinsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//Updates the widget coin counter and plays a little animation
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

//Updates the widget health bar and plays a little animation
void UCoinsWidget::UpdateHealthBar(float Value)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(Value);
		if (HealthObtainedAnimation)
		{
			PlayAnimation(HealthObtainedAnimation, .0f, 1, EUMGSequencePlayMode::Forward, 4.f);
		}
	}
}
