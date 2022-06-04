#include "GameOverWidget.h"
#include "GEPlatformerGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameOverWidget::SetElements(bool bIsGameWon)
{
	AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (GEPGameMode)
	{
		if(bIsGameWon)
		{
			GameOverScoreText->SetText(FText::FromString(FString::FromInt(GEPGameMode->GetTotalCoinsCount()) + 
				"/" + FString::FromInt(GEPGameMode->GetTotalCoinsCount())));
			
			YouLoseTitle->SetVisibility(ESlateVisibility::Hidden);
			YouWinTitle->SetVisibility(ESlateVisibility::Visible);

		}
	}
}