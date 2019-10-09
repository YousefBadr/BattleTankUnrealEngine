#include "TankTrack.h"
#include "Gameframework/Actor.h"
#include "SprungWheel.h"
#include "Engine/World.h"




UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
    auto CurrentThrottle=FMath::Clamp<float>(Throttle, -1, 1);
	DriveTank(CurrentThrottle);
}

void UTankTrack::DriveTank(float CurrentThrottle)
{
    //we cast to UPrimitiveComponent so we can add force.
    //Remember UStaticMeshComponent is also UPrimitiveComponent.

    auto ForceApplied=CurrentThrottle*TrackMaxDrivingForce;
    auto Wheels = GetWheels();
    auto ForcePerWheel=ForceApplied/Wheels.Num();
    for(ASprungWheel* wheel : Wheels)
    {
        wheel->AddDrivingForce(ForcePerWheel);
    }
}

TArray <ASprungWheel*> UTankTrack::GetWheels() const
{
    
}
