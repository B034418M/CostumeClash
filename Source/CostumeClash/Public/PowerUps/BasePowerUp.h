// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpData.h"
#include "GameFramework/Actor.h"
#include "BasePowerUp.generated.h"

class ACostumeClashCharacter;
class UDataTable;

UCLASS(Abstract)
class COSTUMECLASH_API ABasePowerUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePowerUp();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPowerUpData _Data;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* _DataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ACostumeClashCharacter> _PlayerRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
