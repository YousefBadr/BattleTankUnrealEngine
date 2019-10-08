// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Gameframework/Actor.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//we made the MassWheelConstraint the root component because the root component doesn't simulate physics.
	MassWheelConstraint=CreateDefaultSubobject<UPhysicsConstraintComponent>(FName ("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Wheel=CreateDefaultSubobject<UStaticMeshComponent>(FName ("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();	
}

void ASprungWheel::SetupConstraint()
{
	if(GetAttachParentActor())
	{
		auto BodyRoot =Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if(!ensure(BodyRoot))return;
		MassWheelConstraint->UPhysicsConstraintComponent::SetConstrainedComponents(
		BodyRoot,NAME_None,Wheel,NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

