#include "VanishingPlatform.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"


AVanishingPlatform::AVanishingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);

	SMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
	SMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
