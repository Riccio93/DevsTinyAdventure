#include "PauseMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UPauseMenuWidget::UPauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//BeginButton->OnClicked.AddDynamic(this, &UGameStartWidget::BeginGame);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	ExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::BackToMenu);
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ClosePauseMenu);
}

void UPauseMenuWidget::ClosePauseMenu()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
	RemoveFromParent();
}

void UPauseMenuWidget::BackToMenu()
{
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("StartMenuLevel")));
}