// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps/PowerUpSpawningComp.h"
#include "PowerUps/BasePowerUp.h"
#include "PowerUps/Pickup.h"


// Sets default values for this component's properties
UPowerUpSpawningComp::UPowerUpSpawningComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}


// Called when the game starts
void UPowerUpSpawningComp::BeginPlay()
{
	Super::BeginPlay();

	if(_DataTable)
	{
		TArray<FName> rowNames = _DataTable->GetRowNames();
		for (FName RowName : rowNames)
		{
			FPowerUpData* structData = _DataTable->FindRow<FPowerUpData>(RowName, "");
			if(structData->_PowerLevel == _SpawnerLevel && !_PowerUpList.Contains(structData->_Class))
			{
				_PowerUpList.AddUnique(structData->_Class);
			}
		}
	}
	
}


// Called every frame
void UPowerUpSpawningComp::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPowerUpSpawningComp::SpawnPickup()
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

TSubclassOf<ABasePowerUp> UPowerUpSpawningComp::GetRandomPowerUp(EPowerUpClass Class)
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
