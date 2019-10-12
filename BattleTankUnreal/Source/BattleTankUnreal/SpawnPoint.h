// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKUNREAL_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	UFUNCTION(BlueprintCallable, Category  = "Setup")
	void SetWheel(TSubclassOf <AActor> WheelToSet);
	AActor* GetSpawnedActor() const;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TSubclassOf <AActor> SpawnClass;	

	UPROPERTY()	
	AActor* SpawnedActor=nullptr;
};
