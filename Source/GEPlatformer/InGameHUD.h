#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "CoinsWidget.h"
#include "GameStartWidget.h"
#include "PauseMenuWidget.h"

#include "InGameHUD.generated.h"

UCLASS()
class GEPLATFORMER_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CoinsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameStartWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

private:	
	UCoinsWidget* CoinsWidget;
	UGameStartWidget* GameStartWidget;
	UPauseMenuWidget* PauseMenuWidget;
};
