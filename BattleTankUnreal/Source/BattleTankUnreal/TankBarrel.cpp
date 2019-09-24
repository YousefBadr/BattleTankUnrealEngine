// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    //Move the barrel the right amount this frame 
    //Given a max elevation speed and frame time
    RelativeSpeed=FMath::Clamp<float>(RelativeSpeed,-1.0,1.0);
    
    //Elevation change per frame
    auto ElevationChange =RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation =RelativeRotation.Pitch + ElevationChange;
    auto Elevation=FMath::Clamp<float>(RawNewElevation,MinElevationDegrees,MaxElevationDegrees);
    SetRelativeRotation(FRotator(Elevation,0,0));


}

