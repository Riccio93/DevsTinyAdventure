#include "GameStartWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UGameStartWidget::UGameStartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> ClickSoundObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_Click.A_Click'"));
	if (ClickSoundObject.Succeeded())
		ClickSound = ClickSoundObject.Object;
}

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BeginButton->OnClicked.AddDynamic(this, &UGameStartWidget::BeginGame);	
}

void UGameStartWidget::BeginGame()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound, 1.f);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	RemoveFromViewport();
}