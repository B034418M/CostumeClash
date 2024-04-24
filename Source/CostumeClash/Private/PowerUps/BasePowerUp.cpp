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

	if(_DataTable)
	{
		TArray<FName> rowNames = _DataTable->GetRowNames();
		for (FName RowName : rowNames)
		{
			FPowerUpData* structData = _DataTable->FindRow<FPowerUpData>(RowName, "");

			if(structData->_Class == this->GetClass())
			{
				_Data = *structData;
				UE_LOG(LogTemp, Warning, TEXT("_____________________CALLED!______________________"));
			}
		}
	}
}


// Called every frame
void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

