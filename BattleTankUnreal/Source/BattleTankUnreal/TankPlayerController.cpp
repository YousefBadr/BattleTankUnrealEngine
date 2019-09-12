// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTankUnreal.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Components/InputComponent.h"
#include "TankAimingComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
#include "Tank.h"




void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto TankAimingComponent=GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(ensure(TankAimingComponent))
        FoundAimingComponent(TankAimingComponent);
    
}
void ATankPlayerController::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);
AimAtCrossHair();
}

void ATankPlayerController::AimAtCrossHair()
{
    if(!GetPawn())return;//e.g. if not possessing
    auto TankAimingComponent=GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(TankAimingComponent))return;

    FVector HitLocation; //out parameter
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if(bGotHitLocation)
    {
        //tell controlled tank to aim at this point
	    TankAimingComponent->AimAt(HitLocation);
    }
}

//get the world location of linetrace through crosshair
//true if it hits the landscape 
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
    //Find the crosshair position in pixel coordinates
    int32 ViewportSizeX,ViewPortSizeY;
    GetViewportSize(ViewportSizeX,ViewPortSizeY);
    auto ScreenLocation = FVector2D(CrossHairXLocation*ViewportSizeX,
    CrossHairYLocation*ViewPortSizeY);

    //"De-Project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation,LookDirection))
    {
        //Line_Trace along that LookDirection and see what we hit (up to max range)
        return GetLookVectorHitLocation(HitLocation,LookDirection);
    }
    return false;
   
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
    FVector CameraWorldLocation; //To be discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection);
        
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector LookDirection) const
{
   
    auto StartLocation=PlayerCameraManager->GetCameraLocation();
    auto EndLocation=StartLocation+LookDirection*LineTraceRange;
	//line tracing ray casting
	FHitResult HitResult;
    bool HitWorld=GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility);
    if(HitWorld)
        HitLocation=HitResult.Location;   
    else 
        HitLocation=FVector(0);
        
    return true;
}


