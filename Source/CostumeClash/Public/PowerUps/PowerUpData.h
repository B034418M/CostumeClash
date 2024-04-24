// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PowerUpData.generated.h"

class ABasePowerUp;

UENUM(BlueprintType)
enum class EPowerUpClass : uint8
{
	LOW,
	MEDIUM,
	HIGH
};

USTRUCT(BlueprintType)
struct FPowerUpData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString _Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> _Icon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPowerUpClass _PowerLevel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float _Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABasePowerUp> _Class;
};
