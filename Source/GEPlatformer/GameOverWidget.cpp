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

			int GameTimeMinutes = (int)GEPGameMode->GetGameTime() / 60;
			int GameTimeSeconds = (int)GEPGameMode->GetGameTime() % 60;

			if(GameTimeMinutes >= 60)
				GameOverTimeText->SetText(FText::FromString("59 minutes\n59 seconds"));
			else
				GameOverTimeText->SetText(FText::FromString(FString::FromInt(GameTimeMinutes) + " minutes\n" + (FString::FromInt(GameTimeSeconds)) + " seconds"));
		}
	}
}

void UGameOverWidget::RestartGame()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("MainLevel")));
}


void UGameOverWidget::ToMenu()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("StartMenuLevel")));
}