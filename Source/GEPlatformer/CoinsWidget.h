#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "CoinsWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UCoinsWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* CoinsCountText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* CoinObtainedAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HealthObtainedAnimation;

public:
	UCoinsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateCoinsCount(int Value, int Total);

	void UpdateHealthBar(float Value);	
};
