#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

UCLASS()
class GEPLATFORMER_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundWave* ClickSound;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BeginButton;

	UGameStartWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct();

	UFUNCTION()
	void BeginGame();
};
