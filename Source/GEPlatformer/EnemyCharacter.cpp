#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

#include "MainCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SceneComponent->SetupAttachment(GetRootComponent());

	//Configure Capsule Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollisionComponent");
	CapsuleComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->InitCapsuleSize(183.f, 110.f);
	CapsuleComponent->AddRelativeRotation(FRotator(90.f, 0.f, 0.f));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnCapsuleOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnCapsuleOverlapEnd);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComponent");
	BoxComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComponent->InitBoxExtent(FVector(145.f, 65.f, 10.f));
	BoxComponent->AddRelativeLocation(FVector(0.f, 0.f, 125.f));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnBoxOverlapBegin);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SkeletalMeshComponent->AddWorldRotation(FRotator(0.f, -90.f, 0.f));
	SkeletalMeshComponent->AddRelativeLocation(FVector(0.f, 0.f, -90.f));

	AttackDamage = .25f;
	bIsCapsuleOverlapping = false;
}

void AEnemyCharacter::OnCapsuleOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = true;
		MainCharacter->TakeDamage(AttackDamage);
	}
}

void AEnemyCharacter::OnCapsuleOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		bIsCapsuleOverlapping = false;
	}
}

void AEnemyCharacter::OnBoxOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		if(!bIsCapsuleOverlapping)
		{
			this->Destroy();
			MainCharacter->EnemyKilledJump();
			//TArray<FOverlapInfo>* OverlapArray = new TArray<FOverlapInfo>;
			//if(CapsuleComponent->GetOverlapsWithActor(MainCharacter, *OverlapArray));
		}		
	}
}

