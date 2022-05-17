#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//For CapsuleTraceSingleByProfile
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
//For Vector Interpolation
#include "Math/UnrealMathUtility.h"
//For debug messages
#include "Engine/Engine.h"
//For ECC
#include "Engine/EngineTypes.h"

AMainCharacter::AMainCharacter()
{
 	//Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Configure Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(44.f, 82.f);
	/*GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd);*/

	//Create components and attach them
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	
	//Configure Spring arm's defaults
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 5.f;
	SpringArmComponent->bEnableCameraRotationLag = true;	
	SpringArmComponent->CameraRotationLagSpeed = 20.f;
	SpringArmComponent->TargetArmLength = 600.f;

	//Configure Character Movement's defaults...
	GetCharacterMovement()->bOrientRotationToMovement = true; //Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); //...at this rotation rate
    DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed = 600.f;
	SprintMultiplier = 2.5f;
	WalkMultiplier = .5f;
	//...and Jump defaults
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = .2f;
	JumpMaxHoldTime = .3f;
	JumpMaxCount = 2;
	DefaultGravity = 1.f;
	WallSlideDeceleration = 8.f;
	AirJumpForce = 600.f;
	WallJumpForce = -500.f;
	bResetVelocityOnce = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DoubleJumpMontageObject(TEXT("/Game/GEPlatformer/Characters/Devvy/Animations/AM_Devvy_DoubleJump.AM_Devvy_DoubleJump"));
	if(DoubleJumpMontageObject.Succeeded())
		DoubleJumpMontage = DoubleJumpMontageObject.Object;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	JumpChecks();
}

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
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
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
	if(JumpCount < JumpMaxCount)
	{
		if(GetCharacterMovement()->IsFalling())
		{
			
			if(bIsInWallSlide)
			{
				//WallJump
				ACharacter::PlayAnimMontage(DoubleJumpMontage, 1, NAME_None);
				LaunchCharacter((GetActorForwardVector() * WallJumpForce) + FVector(0.f, 0.f, AirJumpForce) , true, true);
			}
			else
			{
				//Double Jump
				ACharacter::PlayAnimMontage(DoubleJumpMontage, 1, NAME_None);
				LaunchCharacter(GetCharacterMovement()->Velocity + FVector(0.f, 0.f, AirJumpForce), true, true);
				JumpCount++;
			}
		}
		else
		{
			//Normal Jump
			ACharacter::Jump();
			JumpCount++;
		}
	}	
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpCount = 0;
	bIsInWallSlide = false;
	GetCharacterMovement()->GravityScale = DefaultGravity;
	GetMovementComponent()->Velocity.Z = 0;
	SetActorRotation(FRotator(0.f, 0.f, GetActorRotation().Vector().Z));
}

void AMainCharacter::JumpChecks()
{
	//Movement logic for the wall jump
	if (GetCharacterMovement()->IsFalling())
	{
		//Check if the player is hitting a wall
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult OutHit;
		UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation(), GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 1.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), TraceTypeQuery2, false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true);
		bIsInWallSlide = OutHit.bBlockingHit;

		if (bIsInWallSlide)
		{
			//Turn in the opposite direction of the wall normal (ready to jump away)
			JumpCount = JumpMaxCount - 1;
			if (GetCharacterMovement()->Velocity.Z <= 0)
			{
				if (bResetVelocityOnce)
				{
					GetCharacterMovement()->Velocity.Z = 0;
					bResetVelocityOnce = false;
				}
				GetCharacterMovement()->GravityScale = .1f;
				FVector CurrentVelocity = GetCharacterMovement()->Velocity;
				GetCharacterMovement()->Velocity = FMath::VInterpTo(CurrentVelocity, FVector(.0f, .0f, CurrentVelocity.Z), GetWorld()->GetDeltaSeconds(), WallSlideDeceleration);
				//SetActorRotation(FRotator(0.f, 0.f, UKismetMathLibrary::MakeRotFromZ(OutHit.Normal).Pitch));
				//SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OutHit.Normal));
				SetActorRotation(UKismetMathLibrary::MakeRotFromX(-OutHit.Normal));
			}
		}
		else
		{
			//When leaving the wall remove "friction"
			GetCharacterMovement()->GravityScale = DefaultGravity;
			bResetVelocityOnce = true;
		}
	}
}


#pragma endregion

//#pragma region Collision Functions
//
//void AMainCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap begin function called");
//
//}
//
//void AMainCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap end function called");
//
//}
//
//#pragma endregion

