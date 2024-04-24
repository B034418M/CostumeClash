// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpSpawner.generated.h"

class APickup;
enum class EPowerUpClass : uint8;
class ABasePowerUp;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COSTUMECLASH_API UPowerUpSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UPowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<ABasePowerUp>> _PowerUpList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPowerUpClass _SpawnerLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APickup> _PickupToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnPickup();

	UFUNCTION()
	TSubclassOf<ABasePowerUp> GetRandomPowerUp(EPowerUpClass Class);
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
};
