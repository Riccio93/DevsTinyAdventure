#include "GameStartWidget.h"

#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UGameStartWidget::UGameStartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BeginButton->OnClicked.AddDynamic(this, &UGameStartWidget::BeginGame);
}

void UGameStartWidget::BeginGame()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
	RemoveFromParent();
}