#include "VanishingPlatform.h"
//Components
#include "Components/BoxComponent.h"
//My Classes
#include "MainCharacter.h"

AVanishingPlatform::AVanishingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	//Mesh Component Setup
	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
	SMeshComponent->SetupAttachment(RootComponent);

	DestroyTime = 1.5f;
}

void AVanishingPlatform::BeginPlay()
{
	Super::BeginPlay();
	//Sets delegate for when the platform gets hit
	SMeshComponent->OnComponentHit.AddDynamic(this, &AVanishingPlatform::OnHit);

	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();
}

void AVanishingPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AMainCharacter* MC = Cast<AMainCharacter>(OtherActor))
	{
		//If the player hits the platform, it starts falling in 1.5 second
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AVanishingPlatform::PlatformFall, 1.f, false, DestroyTime);
	}	
}

void AVanishingPlatform::PlatformFall()
{
	SMeshComponent->SetSimulatePhysics(true);
	//After 6 seconds the platform goes back to the original location
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AVanishingPlatform::RespawnPlatform, 1.f, false, DestroyTime * 4);
}

void AVanishingPlatform::RespawnPlatform()
{
	SMeshComponent->SetSimulatePhysics(false);
	SetActorLocation(OriginalLocation);
	SetActorRotation(OriginalRotation);
}
