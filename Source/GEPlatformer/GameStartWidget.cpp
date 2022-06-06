#include "GameStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
//Components
#include "Components/Button.h"

//Screen that shows the objective and the button mapping
UGameStartWidget::UGameStartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Sound effect
	static ConstructorHelpers::FObjectFinder<USoundWave> ClickSoundObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_Click.A_Click'"));
	if (ClickSoundObject.Succeeded())
		ClickSound = ClickSoundObject.Object;
}

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Delegate for button presses
	BeginButton->OnClicked.AddDynamic(this, &UGameStartWidget::BeginGame);	
}

void UGameStartWidget::BeginGame()
{
	//Hides the mouse cursor and hides the widget
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound, 1.f);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	RemoveFromViewport();
}