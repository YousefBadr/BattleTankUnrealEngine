// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    //Rotate the Turret the right amount this frame 
    //Given a max rotation speed and frame time
    RelativeSpeed=FMath::Clamp<float>(RelativeSpeed,-1,1);
    //Rotation change per frame
    auto RotationChange =RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation =RelativeRotation.Yaw + RotationChange;
    SetRelativeRotation(FRotator(0,RawNewRotation,0));
}

