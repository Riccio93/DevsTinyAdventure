#include "MainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"
//Components
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//My Classes
#include "InGameHUD.h"
#include "Coin.h"
#include "Heart.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Configure Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(25.f, 82.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	//GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd);

	//Create components and attach them
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	
	//Configure Spring arm's defaults
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 4.f;
	SpringArmComponent->bEnableCameraRotationLag = true;	
	SpringArmComponent->CameraRotationLagSpeed = 20.f;
	SpringArmComponent->TargetArmLength = 600.f;

	//Configure Character Movement's defaults...
	GetCharacterMovement()->bOrientRotationToMovement = true;            //Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); //...at this rotation rate
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
	GetCharacterMovement()->AirControl = 1.f; //At 1 the character can use the wall jump to climb a single wall, set at 0.05 if we don't want that

	//Get animation montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DoubleJumpMontageObject(TEXT("/Game/GEPlatformer/Characters/Devvy/Animations/AM_Devvy_DoubleJump.AM_Devvy_DoubleJump"));
	if(DoubleJumpMontageObject.Succeeded())
		DoubleJumpMontage = DoubleJumpMontageObject.Object;

	CurrentCoinsCount = 0;
	TotalCoinsCount = 5;
	MaxHealthValue = 1.f;
	HealthValue = .5f;
	HeartHealthRecover = .25f;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initializes values of the coins/health UI widget
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->InitializeValues(TotalCoinsCount);
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

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
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
		//WallJump
		ACharacter::PlayAnimMontage(DoubleJumpMontage, 1, NAME_None);
		GetCharacterMovement()->Velocity.Z = 0;
		LaunchCharacter((GetActorForwardVector() * WallJumpForwardForce) + FVector(0.f, 0.f, WallJumpVerticalForce), true, true);
	}
	else
	{
		if(JumpCount < JumpMaxCount)
		{
			if(GetCharacterMovement()->IsFalling())
			{
				//Double Jump (in the air)
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
	Super::Jump();
}

void AMainCharacter::WallJumpChecks()
{
	//Movement logic for the wall jump
	if (GetCharacterMovement()->IsFalling())
	{
		//Check if the player is hitting a wall, if so set the bool bIsInWallSlide
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult OutHit;
		//TODO: Check here for the trace type
		UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation(), GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 1.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), TraceTypeQuery2, false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true);
		bIsInWallSlide = OutHit.bBlockingHit;

		if (bIsInWallSlide)
		{
			//Turn in the opposite direction of the wall normal (ready to jump away)
			SetActorRotation(UKismetMathLibrary::MakeRotFromX(-OutHit.Normal));			
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
			//When leaving the wall remove "friction" (lowered gravity)
			GetCharacterMovement()->GravityScale = DefaultGravity;
			bResetVelocityOnce = true;
		}
	}
}



#pragma endregion

#pragma region Collision Functions

void AMainCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//When collecting a coin, destroy it and add a point
	if(ACoin* HitCoin = Cast<ACoin>(OtherActor))
	{
		AddCoinsToCounter(1);		
		OtherActor->Destroy();		
	}

	//When the player collects all coins the game is won
	if(CurrentCoinsCount == TotalCoinsCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "You win!");
	}

	//When collecting an heart, some health is recovered
	if(AHeart* HitHeart = Cast<AHeart>(OtherActor))
	{
		RecoverHealth(HeartHealthRecover);
		OtherActor->Destroy();		
	}	
}

void AMainCharacter::AddCoinsToCounter(int coins)
{
	CurrentCoinsCount += coins;

	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->UpdateCoinsCount(CurrentCoinsCount, TotalCoinsCount);
	}
}



void AMainCharacter::TakeDamage(float Value)
{
	HealthValue -= Value;
	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->UpdateHealth(HealthValue);
	}
	if (HealthValue <= 0)
	{
		//TODO: Death
	}
	else
	{
		//Blink and be indestructible for a certain amount of time??
	}
}

void AMainCharacter::RecoverHealth(float Value)
{
	HealthValue += Value;
	if (HealthValue > MaxHealthValue)
	{
		HealthValue = MaxHealthValue;
	}

	AInGameHUD* InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (InGameHUD)
	{
		InGameHUD->UpdateHealth(HealthValue);
	}
}

//
//void AMainCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap end function called");
//
//}
//

#pragma endregion