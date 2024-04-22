// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.generated.h"

enum class EPowerUpClass : uint8;
class ABasePowerUp;

UCLASS()
class COSTUMECLASH_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<ABasePowerUp>> _PowerUpList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPowerUpClass _SpawnerLevel;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
