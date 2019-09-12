#include "TankAIController.h"
#include "BattleTankUnreal.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto TankAimingComponent=GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(TankAimingComponent))return;
    auto PossessdTank=GetPawn();
    auto PlayerTank=GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!ensure(PlayerTank && PossessdTank))return;
    
    //Move towards the player
    MoveToActor(PlayerTank,AcceptanceRadius);//TODO check radius in CM

    //Aim towards player
    TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

    if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire(); // TODO limit firing rate
	}
    
   
}