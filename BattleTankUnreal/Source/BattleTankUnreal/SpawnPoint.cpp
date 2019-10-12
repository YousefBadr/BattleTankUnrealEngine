// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Gameframework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void USpawnPoint::SetWheel(TSubclassOf <AActor> WheelToSet)
{
	SpawnClass=WheelToSet;
	SpawnedActor=GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());
	if(!ensure(SpawnedActor))return;
	SpawnedActor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor,GetComponentTransform());
}
AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

