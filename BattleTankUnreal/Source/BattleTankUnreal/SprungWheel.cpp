// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Gameframework/Actor.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	//we made the MassWheelConstraint the root component because the root component doesn't simulate physics.
	MassWheelConstraint=CreateDefaultSubobject<UPhysicsConstraintComponent>(FName ("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle=CreateDefaultSubobject<USphereComponent>(FName ("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel=CreateDefaultSubobject<USphereComponent>(FName ("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint=CreateDefaultSubobject<UPhysicsConstraintComponent>(FName ("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this,&ASprungWheel::OnHit);
	SetupConstraint();	
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame+=ForceMagnitude;
}	

void ASprungWheel::SetupConstraint()
{
	if(GetAttachParentActor())
	{
		auto BodyRoot =Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if(!ensure(BodyRoot))return;
		MassWheelConstraint->UPhysicsConstraintComponent::SetConstrainedComponents(
		BodyRoot,NAME_None,Axle,NAME_None);
		
		AxleWheelConstraint->UPhysicsConstraintComponent::SetConstrainedComponents(
		Axle,NAME_None,Wheel,NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame=0;
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
 	Wheel->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame);
}
