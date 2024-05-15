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
			if(!_PowerUpList.Contains(structData->_Class))
			{
				_PowerUpList.AddUnique(structData->_Class);
				UE_LOG(LogTemp, Display, TEXT("___________ADDED A POWERUP_IMGONNABUSS!!!__________"));
			}
		}
	}

	for (auto Element : _ProbabilityMap)
	{
		totalProbability += Element.Value;
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
	/* OLD SYSTEM
	 
	// Works out the percentage chance using all probabilities from the map and if the random number between 0 and 1 is less than or
	// equal to the corresponding decimal, then spawn. i.e 60% chance, if number is <= 0.6, spawn as it has a "theoretically" 60% chance
	
	float* value = _ProbabilityMap.Find(_SpawnerLevel);
	float probability = *value / totalProbability;

	bool bShouldSpawn = FMath::RandRange(0.0f, 1.0f) <= probability;
	*/

	bool bShouldSpawn = (FMath::RandRange(0.0f, 1.0f) <= *_ProbabilityMap.Find(_SpawnerLevel)) ? true : false;
	
	if(bShouldSpawn)
	{
		UE_LOG(LogTemp, Display, TEXT("___________SPAWNING PICKUP__________"));
		
		TSubclassOf<ABasePowerUp> newAbility = GetRandomPowerUp(_SpawnerLevel);

		if(newAbility != nullptr)
		{
			FActorSpawnParameters spawnInfo;
			FRotator rot(0.0f, 0.0f, 0.0f);
			FVector loc = GetOwner()->GetActorLocation();
			loc.Z = 30.0f;
		
			APickup* pickup = GetOwner()->GetWorld()->SpawnActor<APickup>(_PickupToSpawn, loc, rot, spawnInfo);

			if(pickup) pickup->_PowerUpClass = newAbility;
		}
	}
}

TSubclassOf<ABasePowerUp> UPowerUpSpawningComp::GetRandomPowerUp(EPowerUpClass Class)
{
	TArray<TSubclassOf<ABasePowerUp>> possiblePU;

	if(_PowerUpList.Num() > 0)
	{
		for (TSubclassOf<ABasePowerUp> i : _PowerUpList)
		{
			if(IsValid(i))
			{
				if (i.GetDefaultObject()->_Data._PowerLevel == Class)
				{
					possiblePU.Add(i);
				}
			}
		}
	}
	else
	{
		return nullptr;
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
