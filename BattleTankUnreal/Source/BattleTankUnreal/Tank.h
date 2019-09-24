// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKUNREAL_API ATank : public APawn
{
	GENERATED_BODY()
	
public:
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

	// return current health ass a percentage of starting health,between 0 and 1
	UFUNCTION(BluePrintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
private:
	ATank();

	UPROPERTY(EditDefaultsOnly ,Category = "Setup")
	int32 StartingHealth=100;

	UPROPERTY(VisibleAnywhere ,Category = "Health")// as we want to change it only on code
	int32 CurrentHealth=StartingHealth;
};
