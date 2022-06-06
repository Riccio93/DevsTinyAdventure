#include "GameOverWidget.h"
#include <string>
#include "Kismet/GameplayStatics.h"
//Components
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
//My Classes
#include "GEPlatformerGameMode.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Get sound effects
	static ConstructorHelpers::FObjectFinder<USoundWave> GameOverWinSoundObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_GameOverWin.A_GameOverWin'"));
	if (GameOverWinSoundObject.Succeeded())
		GameOverWinSound = GameOverWinSoundObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> GameOverLoseSoundObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_GameOverLose.A_GameOverLose'"));
	if (GameOverLoseSoundObject.Succeeded())
		GameOverLoseSound = GameOverLoseSoundObject.Object;
}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Delegates for button presses
	RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
	BackButton->OnClicked.AddDynamic(this, &UGameOverWidget::ToMenu);	
}

void UGameOverWidget::InitializeWidgetElements(bool bIsGameWon)
{
	//Sets all the dynamic values that appear in the widget (points, time, etc.)
	AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GEPGameMode)
	{
		GameOverScoreText->SetText(FText::FromString(FString::FromInt(GEPGameMode->GetCoinsCount()) +
			"/" + FString::FromInt(GEPGameMode->GetTotalCoinsCount())));

		int GameTimeMinutes = (int)GEPGameMode->GetGameTime() / 60;
		int GameTimeSeconds = (int)GEPGameMode->GetGameTime() % 60;
		if (GameTimeMinutes >= 60)
			GameOverTimeText->SetText(FText::FromString("59 minutes\n59 seconds"));
		else
			GameOverTimeText->SetText(FText::FromString(FString::FromInt(GameTimeMinutes) + " minutes\n" + (FString::FromInt(GameTimeSeconds)) + " seconds"));

		if (bIsGameWon)
		{
			//Win Screen
			UGameplayStatics::PlaySound2D(GetWorld(), GameOverWinSound, 1.f);
			YouWinTitle->SetVisibility(ESlateVisibility::Visible);
			YouLoseTitle->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			//Lose Screen
			UGameplayStatics::PlaySound2D(GetWorld(), GameOverLoseSound, 1.f);
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