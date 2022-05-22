#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "CoinsWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UCoinsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCoinsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateCoinsCount(int Value, int Total);

	void ResetCoins();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCountText;
};
