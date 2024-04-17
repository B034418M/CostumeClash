// Copyright Epic Games, Inc. All Rights Reserved.

#include "CostumeClashGameMode.h"
#include "CostumeClashCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACostumeClashGameMode::ACostumeClashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
