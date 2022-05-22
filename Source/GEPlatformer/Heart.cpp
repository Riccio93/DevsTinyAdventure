#include "Heart.h"
#include "Components/PointLightComponent.h"

//Set default values
AHeart::AHeart()
{
	PrimaryActorTick.bCanEverTick = false;

	PointLightComponent->SetLightColor(FColor(255, 18, 18));

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AHeart::SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetWorldScale3D(FVector(0.65f, 0.65f, 0.65f));
}