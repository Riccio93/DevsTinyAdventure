#include "PauseMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UPauseMenuWidget::UPauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> ClickSoundObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_Click.A_Click'"));
	if (ClickSoundObject.Succeeded())
		ClickSound = ClickSoundObject.Object;
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::BackToMenu);
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ClosePauseMenu);
}

void UPauseMenuWidget::ClosePauseMenu()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound, 1.f);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	RemoveFromViewport();
	ExitButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::BackToMenu);
	ResumeButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::ClosePauseMenu);
}

void UPauseMenuWidget::BackToMenu()
{
	//UGameplayStatics::PlaySound2D(GetWorld(), ClickSound, 1.f);
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("StartMenuLevel")));
}