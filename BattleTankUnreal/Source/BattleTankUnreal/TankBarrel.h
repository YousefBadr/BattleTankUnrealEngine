// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class BATTLETANKUNREAL_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed and 1 is max up speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly ,Category = "Setup")
	float MaxDegreesPerSecond=10; //sensible defualt 

	UPROPERTY(EditDefaultsOnly ,Category = "Setup")
	float MaxElevationDegrees=40;

	UPROPERTY(EditDefaultsOnly ,Category = "Setup")
	float MinElevationDegrees=0;
};