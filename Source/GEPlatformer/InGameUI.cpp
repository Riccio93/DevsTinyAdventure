#include "InGameUI.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	GenerateRandom();

	PauseButton->OnClicked.AddUniqueDynamic(this, &UInGameUI::OnPauseButtonClicked);
}

void UInGameUI::GenerateRandom()
{
	int RandomNumber = FMath::RandRange(0, 100);
	InGameText->SetText(FText::AsNumber(RandomNumber));
}

void UInGameUI::OnPauseButtonClicked()
{
	GenerateRandom();
}