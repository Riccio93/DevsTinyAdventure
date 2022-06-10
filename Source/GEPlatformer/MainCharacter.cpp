#include "MainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"
#include "Sound/SoundCue.h"

//Components
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//My Classes
#include "InGameHUD.h"
#include "GEPlatformerGameMode.h"
#include "Coin.h"
#include "Heart.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Components setup
	GetCapsuleComponent()->InitCapsuleSize(25.f, 82.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 4.f;
	SpringArmComponent->bEnableCameraRotationLag = true;	
	SpringArmComponent->CameraRotationLagSpeed = 20.f;
	SpringArmComponent->TargetArmLength = 600.f;

	//Configure Character Movement's defaults...
	GetCharacterMovement()->bOrientRotationToMovement = true;            //Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); //...at this rotation rate
	bUseControllerRotationYaw = false;
    DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed = 600.f;
	SprintMultiplier = 2.5f;
	WalkMultiplier = .5f;
	//...and Jumping defaults
	GetCharacterMovement()->JumpZVelocity = 900.f;
	GetCharacterMovement()->AirControl = .1f;
	JumpMaxHoldTime = .3f;
	JumpMaxCount = 2;
	DefaultGravity = 4.f;
	WallSlideDeceleration = 8.f;
	AirJumpForce = 1300.f;
	WallJumpForwardForce = -550.f;
	WallJumpVerticalForce = 1300.f;
	bResetVelocityOnce = true;
	GetCharacterMovement()->AirControl = .05f; //At 1 the character can use the wall jump to climb a single wall, at 0.05 he can't
	
	//Get animation montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DoubleJumpMontageObject(TEXT("/Game/GEPlatformer/Characters/Devvy/Animations/AM_Devvy_DoubleJump.AM_Devvy_DoubleJump"));
	if(DoubleJumpMontageObject.Succeeded())
		DoubleJumpMontage = DoubleJumpMontageObject.Object;

	//Get audio files
	static ConstructorHelpers::FObjectFinder<USoundCue> CoinSoundCueObject(TEXT("SoundCue'/Game/GEPlatformer/Audio/A_Coin_Cue.A_Coin_Cue'"));
	if (CoinSoundCueObject.Succeeded())
		CoinSoundCue = CoinSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> JumpSoundCueObject(TEXT("SoundCue'/Game/GEPlatformer/Audio/A_Jump_Cue.A_Jump_Cue'"));
	if (JumpSoundCueObject.Succeeded())
		JumpSoundCue = JumpSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> HeartSoundCueObject(TEXT("SoundCue'/Game/GEPlatformer/Audio/A_Heart2_Cue.A_Heart2_Cue'"));
	if (HeartSoundCueObject.Succeeded())
		HeartSoundCue = HeartSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> EnemyDeathSoundCueObject(TEXT("SoundCue'/Game/GEPlatformer/Audio/A_EnemyDeath_Cue.A_EnemyDeath_Cue'"));
	if (EnemyDeathSoundCueObject.Succeeded())
		EnemyDeathSoundCue = EnemyDeathSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> TakeDamageSoundCueObject(TEXT("SoundCue'/Game/GEPlatformer/Audio/A_TakeDamage_Cue.A_TakeDamage_Cue'"));
	if (TakeDamageSoundCueObject.Succeeded())
		TakeDamageSoundCue = TakeDamageSoundCueObject.Object;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initializes values of the coins/health UI widget
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (InGameHUD && GEPGameMode)
	{
		InGameHUD->InitializeValues(GEPGameMode->GetTotalCoinsCount());
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WallJumpChecks();
}

#pragma region Input Functions

//Binds functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent); //If the component doesn't exist it just stops the execution (it's like C's assert())
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprinting);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMainCharacter::Walk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AMainCharacter::StopWalking);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMainCharacter::OpenPauseMenuInHUD);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

//Function that opens the pause menu using the ESC key
void AMainCharacter::OpenPauseMenuInHUD()
{
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->OpenPauseMenu();
	}
}

#pragma endregion

#pragma region Movement Functions

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0); //Yaw = Y value

		//Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * SprintMultiplier;
}

void AMainCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void AMainCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * WalkMultiplier;
}

void AMainCharacter::StopWalking()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

#pragma endregion

#pragma region Jumps Functions

void AMainCharacter::Jump()
{
	if (bIsInWallSlide)
	{
		//If the character is touching a Jumpwall, make a walljump when pressing space
		ACharacter::PlayAnimMontage(DoubleJumpMontage, 1, NAME_None);
		GetCharacterMovement()->Velocity.Z = 0;
		//Launches the character up and in the direction of the normal to the wall
		LaunchCharacter((GetActorForwardVector() * WallJumpForwardForce) + FVector(0.f, 0.f, WallJumpVerticalForce), true, true);
		//SFX
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSoundCue, GetActorLocation(), 1.f);
	}
	else
	{
		if(JumpCount < JumpMaxCount)
		{
			//If the character is in the air, make a double jump
			if(GetCharacterMovement()->IsFalling())
			{
				ACharacter::PlayAnimMontage(DoubleJumpMontage, 1, NAME_None);
				GetCharacterMovement()->Velocity.Z = 0;
				LaunchCharacter(GetCharacterMovement()->Velocity + FVector(0.f, 0.f, AirJumpForce), true, true);
				JumpCount++;
			}
			else
			{
				//Normal Jump
				Super::Jump();
				JumpCount++;
			}
			//SFX
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSoundCue, GetActorLocation(), 1.f);
		}	
	}
}

//Reset everything when touching the ground after a jump (normal, double or wall jump)
void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpCount = 0;
	bIsInWallSlide = false;
	GetCharacterMovement()->GravityScale = DefaultGravity;
	GetMovementComponent()->Velocity.Z = 0;
	SetActorRotation(FRotator(0.f, 0.f, GetActorRotation().Vector().Z));
}

void AMainCharacter::EnemyKilledJump()
{
	//Automatically jump when killing an enemy from above
	Super::Jump();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemyDeathSoundCue, GetActorLocation(), 2.f);
}

void AMainCharacter::WallJumpChecks()
{
	//Movement logic for the wall jump
	if (GetCharacterMovement()->IsFalling())
	{
		//Check if the player is hitting a wall suitable for wall jumps, if so set the bool bIsInWallSlide
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult OutHit;
		//Trace channel with walls suitable for wall jumps (JumpWall in editor)
		ETraceTypeQuery JumpWallTrace = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel3);
		UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation(), GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 1.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), JumpWallTrace, false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true);
		bIsInWallSlide = OutHit.bBlockingHit;	

		if (bIsInWallSlide)
		{
			//Turn in the opposite direction of the wall normal (ready to jump away)
			SetActorRotation(UKismetMathLibrary::MakeRotFromX(-OutHit.Normal));	
			//Even if the character has no jumps left, after a wall jump he can always make a double jump
			JumpCount = JumpMaxCount - 1;
			if (GetCharacterMovement()->Velocity.Z <= 0)
			{
				//The moment the character enters the wall slide the vertical velocity is set to 0 (to simulate the immediate friction with the wall)...
				if (bResetVelocityOnce)
				{
					GetCharacterMovement()->Velocity.Z = 0;
					bResetVelocityOnce = false;
				}
				//...then the character slowly slides down
				GetCharacterMovement()->GravityScale = .1f;
				FVector CurrentVelocity = GetCharacterMovement()->Velocity;
				GetCharacterMovement()->Velocity = FMath::VInterpTo(CurrentVelocity, FVector(.0f, .0f, CurrentVelocity.Z), GetWorld()->GetDeltaSeconds(), WallSlideDeceleration);			
			}
		}
		else
		{
			//When leaving the wall remove "friction" with it (lowered gravity)
			GetCharacterMovement()->GravityScale = DefaultGravity;
			bResetVelocityOnce = true;
		}
	}
}

#pragma endregion

#pragma region Collision Functions

void AMainCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the character touches the kill plane, he's dead
	if(OtherActor->ActorHasTag("KillPlane"))
	{
		AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
		PlayerTakeDamage(GEPGameMode->MaxHealthValue);
	}

	//When collecting a coin, destroy it and add a point
	if(ACoin* HitCoin = Cast<ACoin>(OtherActor))
	{
		AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
		if(GEPGameMode)
		{
			GEPGameMode->UpdateCoins(1);
		}
		//SFX
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinSoundCue, HitCoin->GetActorLocation(), 1.75f);
		OtherActor->Destroy();
	}

	//When collecting an heart, destroy it and recover some health
	if(AHeart* HitHeart = Cast<AHeart>(OtherActor))
	{
		AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
		if (GEPGameMode)
		{
			GEPGameMode->UpdateHealth(GEPGameMode->HeartHealthRecover);
		}
		//SFX
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HeartSoundCue, HitHeart->GetActorLocation(), 2.5f);
		OtherActor->Destroy();	
	}	
}

void AMainCharacter::PlayerTakeDamage(float Value)
{
	AGEPlatformerGameMode* GEPGameMode = Cast<AGEPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if(GEPGameMode)
	{
		GEPGameMode->UpdateHealth(-Value);
	}
	//SFX
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), TakeDamageSoundCue, GetActorLocation(), 1.f);

	//TODO: Blink and be indestructible for a certain amount of time??
}

#pragma endregion