#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//Components
#include "Components/WidgetComponent.h"
//My Classes
#include "CoinsWidget.h"
#include "GameStartWidget.h"
#include "PauseMenuWidget.h"
#include "GameOverWidget.h"

#include "InGameHUD.generated.h"

UCLASS()
class GEPLATFORMER_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	UCoinsWidget* CoinsWidget;
	UPROPERTY()
	UGameStartWidget* GameStartWidget;
	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;
	UPROPERTY()
	UGameOverWidget* GameOverWidget;

public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void InitializeValues(int totalCoinsCount);

	UFUNCTION()
	void UpdateCoinsCount(int Value, int Total);

	UFUNCTION()
	void UpdateHealth(float Value);

	void OpenPauseMenu();

	void ShowGameOverScreen(bool bIsGameWon);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CoinsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameStartWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameOverWidgetClass;	
};
