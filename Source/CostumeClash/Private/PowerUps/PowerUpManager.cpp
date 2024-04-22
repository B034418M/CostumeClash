// Fill out your copyright notice in the Description page of Project Settings.


#include "CostumeClash/Public/PowerUps/PowerUpManager.h"

#include "CostumeClash/CostumeClashCharacter.h"
#include "CostumeClash/Public/PowerUps/BasePowerUp.h"


// Sets default values for this component's properties
UPowerUpManager::UPowerUpManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	OnUseAbilityDelegate.AddUniqueDynamic(this, &UPowerUpManager::UseAbility);
	OnPickupDelegate.AddUniqueDynamic(this, &UPowerUpManager::OnPickup);

	bUsingAbility = false;
}


void UPowerUpManager::UseAbility()
{
	//UE_LOG(LogTemp, Display, TEXT("______________________DELEGATE WORKING___________________"));
	
	if(_CurrentPowerUp && _PlayerRef)
	{
		if(!bUsingAbility)
		{
			FRotator rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters spawnParameters;
			ABasePowerUp* newPowerup = GetOwner()->GetWorld()->SpawnActor<ABasePowerUp>(_CurrentPowerUp, _PlayerRef->GetTransform().GetLocation(), rotation, spawnParameters);

			if(newPowerup->_Data._Duration > 0)
			{
				bUsingAbility = true;
				GetOwner()->GetWorld()->GetTimerManager().SetTimer(boolTimerHandle, FTimerDelegate::CreateLambda([=]()
				{
					bUsingAbility = false;
					GetOwner()->GetWorld()->GetTimerManager().ClearTimer(boolTimerHandle);
				}), newPowerup->_Data._Duration, false);
			}

			_CurrentPowerUp = nullptr;
			newPowerup->_PlayerRef = _PlayerRef;
			newPowerup->UseAbility();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("__________________TIMER ACTIVE_________________"));
		}
	}

	/* Debugging things
	if(!IsValid(_CurrentPowerUp))
	{
		UE_LOG(LogTemp, Warning, TEXT("_______NO POWERUP REF______________"));
	}
	if(!IsValid(_PlayerRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("_______NO PLAYER REF______________"));
	}
	*/
	
}

void UPowerUpManager::OnPickup(UClass* newPickup)
{
	_CurrentPowerUp = newPickup;
}

// Called when the game starts
void UPowerUpManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPowerUpManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	
}
