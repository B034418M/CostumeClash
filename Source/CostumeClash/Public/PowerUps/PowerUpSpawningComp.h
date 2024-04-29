// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpSpawningComp.generated.h"

class APickup;
enum class EPowerUpClass : uint8;
class ABasePowerUp;
class UDataTable;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COSTUMECLASH_API UPowerUpSpawningComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerUpSpawningComp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* _DataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<ABasePowerUp>> _PowerUpList;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EPowerUpClass, float> _ProbabilityMap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPowerUpClass _SpawnerLevel;
	
	UFUNCTION(BlueprintCallable)
	void SpawnPickup();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
	float totalProbability;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APickup> _PickupToSpawn;

	

	UFUNCTION()
	TSubclassOf<ABasePowerUp> GetRandomPowerUp(EPowerUpClass Class);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
