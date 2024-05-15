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
			if(_CurrentPowerUp->_Data._Duration > 0)
			{
				bUsingAbility = true;
				
				_CurrentPowerUp->_PlayerRef = _PlayerRef;
				_CurrentPowerUp->UseAbility();
				
				GetOwner()->GetWorld()->GetTimerManager().SetTimer(boolTimerHandle, FTimerDelegate::CreateLambda([=]()
				{
					bUsingAbility = false;

					_CurrentPowerUp->Destroy();
					_CurrentPowerUp = nullptr;
					
					GetOwner()->GetWorld()->GetTimerManager().ClearTimer(boolTimerHandle);
				}), _CurrentPowerUp->_Data._Duration + 0.1f, false);
			}
			else
			{
				_CurrentPowerUp->_PlayerRef = _PlayerRef;
				_CurrentPowerUp->UseAbility();

				_CurrentPowerUp->Destroy();
				_CurrentPowerUp = nullptr;
			}
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
	if(!bUsingAbility)
	{
		if(_CurrentPowerUp)
		{
			_CurrentPowerUp->Destroy();
		}
		if(IsValid(newPickup))
		{
			FRotator rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters spawnParameters;
			_CurrentPowerUp = GetOwner()->GetWorld()->SpawnActor<ABasePowerUp>(newPickup, _PlayerRef->GetTransform().GetLocation(), rotation, spawnParameters);
			_CurrentPowerUp->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Power Up"));
		}
	}
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
