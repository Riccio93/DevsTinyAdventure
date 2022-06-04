#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* GameOverScoreText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* YouLoseTitle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* YouWinTitle;

public:
	UGameOverWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetElements(bool bIsGameWon);
};
