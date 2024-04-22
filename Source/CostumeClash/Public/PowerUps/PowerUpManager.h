// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpManager.generated.h"

enum class EPowerUpClass : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseAbilitySignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickupSignature, UClass*, PickupClass);

class ACostumeClashCharacter;
class ABasePowerUp;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COSTUMECLASH_API UPowerUpManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerUpManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	FOnUseAbilitySignature OnUseAbilityDelegate;
	FOnPickupSignature OnPickupDelegate;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bUsingAbility;

	FTimerHandle boolTimerHandle;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABasePowerUp> _CurrentPowerUp;

	// TODO REPLACE IF CHARACTER CLASS CHANGES
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<ACostumeClashCharacter> _PlayerRef;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<EPowerUpClass, float> _ProbabilityMap;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<ABasePowerUp>> _PowerupList;

	UFUNCTION()
	void UseAbility();
	
	UFUNCTION()
	void OnPickup(UClass* newPickup);

	UFUNCTION(BlueprintCallable)
	void AddPowerUp(EPowerUpClass powerUpLevel);

	UFUNCTION()
	TArray<ABasePowerUp*> GetRandomPowerUp(EPowerUpClass Class);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
};
