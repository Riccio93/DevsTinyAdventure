#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GEPLATFORMER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;	

	//Gameplay Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float WalkMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float SprintMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bIsInWallSlide;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	int JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	int AirJumpForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	int WallJumpForwardForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	int WallJumpVerticalForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float DefaultGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float WallSlideDeceleration;

	bool bResetVelocityOnce;
	float DefaultWalkSpeed;
	UAnimMontage* DoubleJumpMontage;

	//Sound effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* CoinSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* JumpSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HeartSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* EnemyDeathSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* TakeDamageSoundCue;

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OpenPauseMenuInHUD();
	
	//Movement and jump functions
	void MoveForward(float value);
	void MoveRight(float value);
	void Sprint();
	void StopSprinting();
	void Walk();
	void StopWalking();
	void Jump();
	void Landed(const FHitResult& Hit);	

	//Collision functions
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	//Gameplay functions
	void PlayerTakeDamage(float Value);
	void RecoverHealth(float Value);
	void AddCoinsToCounter(int coins);
	void EnemyKilledJump();

	//Return sub objects
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return CameraComponent; }

private:
	void WallJumpChecks();
};