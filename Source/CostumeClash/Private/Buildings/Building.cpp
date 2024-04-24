// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building.h"

#include "PowerUps/PowerUpSpawningComp.h"


// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_PowerUpSpawner = CreateDefaultSubobject<UPowerUpSpawningComp>(TEXT("Power Up Spawner"));
	_PowerUpSpawner->RegisterComponent();
	this->AddInstanceComponent(_PowerUpSpawner);
}

void ABuilding::Destroy()
{
	_PowerUpSpawner->SpawnPickup();
	K2_DestroyActor();
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

