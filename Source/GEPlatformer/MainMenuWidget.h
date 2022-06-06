#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* QuitButton;

	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void PlayGame();	
};
