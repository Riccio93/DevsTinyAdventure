#include "RatEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundAttenuation.h"


ARatEnemy::ARatEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent->InitBoxExtent(FVector(90.f, 90.f, 10.f));
	BoxComponent->AddRelativeLocation(FVector(0.f, 0.f, 125.f));

	SkeletalMeshComponent->AddWorldRotation(FRotator(0.f, -90.f, 0.f));
	SkeletalMeshComponent->AddRelativeLocation(FVector(0.f, 0.f, -90.f));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave> CrabWalkingSoundWaveObject(TEXT("SoundWave'/Game/GEPlatformer/Audio/A_CrabFootstep.A_CrabFootstep'"));
	if (CrabWalkingSoundWaveObject.Succeeded())
		CrabWalkingSoundWave = CrabWalkingSoundWaveObject.Object;	

	static ConstructorHelpers::FObjectFinder<USoundAttenuation> SoundAttenuationObject(TEXT("SoundAttenuation'/Game/GEPlatformer/Audio/ATT_Enemy.ATT_Enemy'"));
	if (SoundAttenuationObject.Succeeded())
		SoundAttenuation = SoundAttenuationObject.Object;
};

void ARatEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Set crab's Walking sound
	AudioComponent->SetSound(CrabWalkingSoundWave);
	AudioComponent->AttenuationSettings = SoundAttenuation;
	AudioComponent->SetVolumeMultiplier(.6f);
	AudioComponent->Play();
}



APatrolPath* ARatEnemy::GetPatrolPath()
{
	return PatrolPath;
}

int ARatEnemy::GetNumberOfPoints()
{
	return PatrolPath->NumberOfPoints();
}