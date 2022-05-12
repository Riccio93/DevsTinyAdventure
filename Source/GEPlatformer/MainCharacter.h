#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GEPLATFORMER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	float DefaultWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float WalkMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float SprintMultiplier;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	//UAnimMontage* DoubleJumpMontage;

public:
	AMainCharacter();

	//Base turn rate, in deg/sec
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;*/

	//Base look up/down rate, in deg/sec
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;*/

//protected:
//	virtual void BeginPlay() override;
//
//public:	
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void Sprint();
	void StopSprinting();
	void Walk();
	void StopWalking();
	void Jump();
	//void TurnAtRate(float value);
	//void LookUpAtRate(float value);

	/** Return subobjects **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return CameraComponent; }
};
