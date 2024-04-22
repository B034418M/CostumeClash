// Fill out your copyright notice in the Description page of Project Settings.


#include "CostumeClash/Public/PowerUps/BasePowerUp.h"


// Sets default values
ABasePowerUp::ABasePowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePowerUp::UseAbility_Implementation()
{
	if(_Data._Name != "")
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *_Data._Name);
	}
}

// Called when the game starts or when spawned
void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

