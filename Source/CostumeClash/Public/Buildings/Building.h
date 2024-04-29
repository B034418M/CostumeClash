// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class UPowerUpSpawningComp;

UCLASS()
class COSTUMECLASH_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuilding();

	UFUNCTION(BlueprintCallable)
	void Destroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPowerUpSpawningComp> _PowerUpSpawner;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> _Mesh;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
