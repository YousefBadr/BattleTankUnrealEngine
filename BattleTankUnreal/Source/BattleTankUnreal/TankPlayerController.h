// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"//must be last include

class UTankAimingComponent;
/**
 * Resposible for helping the player aim.
 */
UCLASS()
class BATTLETANKUNREAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef); //No need to implement in C++
private:
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange=1000000.f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation=0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation=0.2;
	
	bool GetLookDirection(FVector2D ScreenLocation,FVector &LookDirection) const;

	/*start the tank moving the barrel so that a shot would 
	hit where the crosshair interacts the world*/
	void AimAtCrossHair();

	//returns an out parameter ,true if it hits landscape
	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookVectorHitLocation(FVector &HitLocation, FVector LookDirection) const;
	
	
};