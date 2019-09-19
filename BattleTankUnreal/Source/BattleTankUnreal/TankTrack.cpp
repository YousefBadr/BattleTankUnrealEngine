#include "TankTrack.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"




UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}
void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);
}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTank();
    ApplySidewaysForce();
    CurrentThrottle=0;
}
void UTankTrack::ApplySidewaysForce()
{
    auto SlippageSpeed=FVector::DotProduct(GetComponentVelocity(),GetRightVector());
    
    //Work-out the requird acceleration this frame to correct
    //Divided by DeltaTime because we need to know the acceleration needed per frame.
    auto DeltaTime=GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
    
    //Calculate and apply sideways (F = n a)
    //GetOwner returns Tank_BP not Tank root
    //We Casted as we wanted to get more functions including GetMass 
    auto TankRoot= Cast <UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce=(TankRoot->GetMass()*CorrectionAcceleration)/2; //Two tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
CurrentThrottle=FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTank()
{
    auto ForceApplied=GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
    auto ForceLocation=GetComponentLocation();
    
    //we cast to UPrimitiveComponent so we can add force.
    //Remember UStaticMeshComponent is also UPrimitiveComponent.
    auto TankRoot=Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}
