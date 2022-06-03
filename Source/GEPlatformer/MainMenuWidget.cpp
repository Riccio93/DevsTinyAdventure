#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
}

void UMainMenuWidget::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting the game..."));
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMainMenuWidget::PlayGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Playing the game!"));
	UGameplayStatics::OpenLevel((UObject*)GetGameInstance(), FName(TEXT("MainLevel")));
}
