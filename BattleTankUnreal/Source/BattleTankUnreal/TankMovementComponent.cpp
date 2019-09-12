#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet,UTankTrack* RightTrackToSet)
{
    if(!ensure(LeftTrackToSet && RightTrackToSet)) return;
    LeftTrack=LeftTrackToSet;
    RightTrack=RightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    //No need to call Super as we are replacing the functionality
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention=MoveVelocity.GetSafeNormal();
    
    auto ForwardThrow=FVector::DotProduct(TankForward,AIForwardIntention); //COS function order doesn't matter
    auto RightThrow=FVector::CrossProduct(TankForward,AIForwardIntention).Z;
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow);
    
    //UE_LOG(LogTemp,Warning,TEXT("%s vectoring to %s"),*TankName,*MoveVelocityString)
}