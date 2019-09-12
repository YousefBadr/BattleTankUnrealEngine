#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
//Depends on movement component via pathfinding system

/**
 * 
 */
UCLASS()
class BATTLETANKUNREAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	

};
