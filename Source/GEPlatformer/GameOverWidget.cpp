#include "GameOverWidget.h"
#include "GEPlatformerGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include <string>
#include "Kismet/GameplayStatics.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
	BackButton->OnClicked.AddDynamic(this, &UGameOverWidget::ToMenu);	
}

void UGameOverWidget::InitializeWidgetElements(bool bIsGameWon)
{
	AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (GEPGameMode)
	{
		GameOverScoreText->SetText(FText::FromString(FString::FromInt(GEPGameMode->GetTotalCoinsCount()) +
			"/" + FString::FromInt(GEPGameMode->GetTotalCoinsCount())));

		int GameTimeMinutes = (int)GEPGameMode->GetGameTime() / 60;
		int GameTimeSeconds = (int)GEPGameMode->GetGameTime() % 60;

		if (GameTimeMinutes >= 60)
			GameOverTimeText->SetText(FText::FromString("59 minutes\n59 seconds"));
		else
			GameOverTimeText->SetText(FText::FromString(FString::FromInt(GameTimeMinutes) + " minutes\n" + (FString::FromInt(GameTimeSeconds)) + " seconds"));

		if (bIsGameWon)
		{
			YouWinTitle->SetVisibility(ESlateVisibility::Visible);
			YouLoseTitle->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			YouWinTitle->SetVisibility(ESlateVisibility::Hidden);
			YouLoseTitle->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UGameOverWidget::RestartGame()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(*GetWorld()->GetName()), false);
}


void UGameOverWidget::ToMenu()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("StartMenuLevel")));
}