#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "MainMenuWidget.h"

#include "MainMenuHUD.generated.h"

UCLASS()
class GEPLATFORMER_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
private:
	UMainMenuWidget* MainMenuWidget;
	
};
