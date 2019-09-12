// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState: uint8 //uint8 can hold up to 256 condition
{
Reloading,
Aiming,
Locked,
OutOfAmmo
};

//Forward Declaration
class UTankBarrel; 
class UTankTurret; 
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKUNREAL_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:		
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category  = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;


	EFiringState GetFiringState() const;
	
protected:
	UFUNCTION(BlueprintCallable, Category  = "Setup")
	void Initialise(UTankBarrel* BarrelToSet,UTankTurret* TurretToSet);

 	UPROPERTY(BlueprintReadOnly, Category= "State")
	EFiringState FiringState=EFiringState::Reloading;

	int RoundsLeft = 3;
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving();

	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelAndTurretTowards(FVector AimDirection);

	UTankBarrel* Barrel=nullptr;	
	UTankTurret* Turret=nullptr;
	double LastFireTime=0;
	FVector AimDirection;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed=4000;//sinsible starting value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf <AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds=3;	
};
