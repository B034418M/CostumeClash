﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps/PowerUpSpawner.h"
#include "PowerUps/BasePowerUp.h"
#include "PowerUps/Pickup.h"


// Sets default values
UPowerUpSpawner::UPowerUpSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UPowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPowerUpSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerUpSpawner::SpawnPickup()
{
	FActorSpawnParameters spawnInfo;
	FRotator rot(0.0f, 0.0f, 0.0f);
	FVector loc = GetOwner()->GetActorLocation();
		
	APickup* pickup = GetOwner()->GetWorld()->SpawnActor<APickup>(_PickupToSpawn, loc, rot, spawnInfo);

	TSubclassOf<ABasePowerUp> newAbility = GetRandomPowerUp(_SpawnerLevel);

	if(newAbility)
	{
		pickup->_PowerUpClass = newAbility;
	}

}

TSubclassOf<ABasePowerUp> UPowerUpSpawner::GetRandomPowerUp(EPowerUpClass Class)
{
	TArray<TSubclassOf<ABasePowerUp>> possiblePU;

	for (TSubclassOf<ABasePowerUp> i : _PowerUpList)
	{
		if (i.GetDefaultObject()->_Data._PowerLevel == Class)
		{
			possiblePU.Add(i);
		}
	}
	
	int totalPUNum = possiblePU.Num();
	TSubclassOf<ABasePowerUp> newAbility;

	if(totalPUNum > 0)
	{
		int randomIndex = FMath::RandRange(0, totalPUNum - 1); 

		newAbility = possiblePU[randomIndex];

		verify(newAbility != nullptr);
	}
	return newAbility;
}


