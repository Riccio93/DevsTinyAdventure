#include "VanishingPlatform.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"


AVanishingPlatform::AVanishingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
	SMeshComponent->SetupAttachment(RootComponent);

	DestroyTime = 1.5f;
}

void AVanishingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SMeshComponent->OnComponentHit.AddDynamic(this, &AVanishingPlatform::OnHit);
}

void AVanishingPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AMainCharacter* MC = Cast<AMainCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("In ONHIT"));
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AVanishingPlatform::SelfDestruct, 1.f, false, DestroyTime);
	}	
}

void AVanishingPlatform::SelfDestruct()
{
	Destroy();
}
