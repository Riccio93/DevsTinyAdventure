// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class GEPLATFORMER_API APatrolPath : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> PatrolPoints;

	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

	FVector getPatrolPoint(int const index) const;
	int NumberOfPoints() const;
};
