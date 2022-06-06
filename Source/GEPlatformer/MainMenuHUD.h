#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//Components
#include "Components/WidgetComponent.h"
//My Classes
#include "MainMenuWidget.h"

#include "MainMenuHUD.generated.h"

UCLASS()
class GEPLATFORMER_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

	UMainMenuWidget* MainMenuWidget;

public:
	AMainMenuHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;	
};
