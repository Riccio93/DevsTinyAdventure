#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

UCLASS()
class UInGameUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	void GenerateRandom();

	UFUNCTION()
	void OnPauseButtonClicked();

	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* InGameText;

	UPROPERTY( meta = ( BindWidget ) )
	class UButton* PauseButton;
};