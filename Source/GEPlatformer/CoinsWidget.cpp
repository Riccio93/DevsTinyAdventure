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
	}
}

void UCoinsWidget::ResetCoins()
{
	if(CoinsCountText)
	{
		CoinsCountText->SetText(FText::FromString(FString::FromInt(0)));
	}
}
