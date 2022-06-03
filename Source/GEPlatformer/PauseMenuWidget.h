#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ExitButton;

	UPauseMenuWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct();

	UFUNCTION()
	void ClosePauseMenu();

	UFUNCTION()
	void BackToMenu();

};
