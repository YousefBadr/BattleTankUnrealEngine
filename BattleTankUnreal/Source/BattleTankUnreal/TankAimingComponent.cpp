// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
//Runtime/Engine/Classes/



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)) return false;
	return !(AimDirection.Equals(Barrel->GetForwardVector(),0.01));
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0)
		FiringState = EFiringState::OutOfAmmo;
	else if((FPlatformTime::Seconds()-LastFireTime)<ReloadTimeInSeconds)
		FiringState=EFiringState::Reloading;
	else if(IsBarrelMoving())
		FiringState=EFiringState::Aiming;
	else 
		FiringState=EFiringState::Locked;

}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::BeginPlay() 
{
	Super::BeginPlay();
	
	//So that first fire is after initial reload
	LastFireTime=FPlatformTime::Seconds();
}
void UTankAimingComponent::Fire()
{
	if(FiringState != EFiringState::Reloading && RoundsLeft>0)
	{
		if(!ensure(Barrel))return;
		if(!ensure(ProjectileBluePrint))return;
		auto Projectile=GetWorld()->SpawnActor<AProjectile> (ProjectileBluePrint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime=FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//auto OurTankName=GetOwner()->GetName(); 
	if (!ensure(Barrel && Turret)){return;}
	auto BarrelLocation=Barrel->GetComponentLocation();
	FVector OutLaunchVelocity;
	FVector StartLocation=Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the launch Velocity
	bool bHaveAimSolution=UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if(bHaveAimSolution)
		{
		AimDirection=OutLaunchVelocity.GetSafeNormal();
		//auto OurTankName=GetOwner()->GetName(); 
		//auto Time=GetWorld()->GetTimeSeconds();
    	//UE_LOG(LogTemp,Warning,TEXT("%s aiming at %s aim solution found"),*OurTankName,*HitLocation.ToString())
		MoveBarrelAndTurretTowards(AimDirection);
		}
		else
		{
		//if no solution is found
		}	
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	if(!ensure(BarrelToSet && TurretToSet)) return;
	Barrel=BarrelToSet;
	Turret=TurretToSet;
}
void UTankAimingComponent::MoveBarrelAndTurretTowards(FVector AimDirection)
{
	//Work out Differance between current barrel rotation and AimDirection
	if(!ensure(Barrel && Turret)) return;
	auto BarrelRotator=Barrel->GetForwardVector().Rotation();
	auto AimAsRotator =AimDirection.Rotation();
	auto DeltaRotator=AimAsRotator-BarrelRotator;
	
	// Always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->Rotate(DeltaRotator.Yaw);
	else //Avoid going the long-way round
		Turret->Rotate(-DeltaRotator.Yaw);
}


