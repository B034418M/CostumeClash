// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectLibraryParser.generated.h"

/**
 * 
 */
UCLASS()
class COSTUMECLASH_API UObjectLibraryParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Object Library Parsing")
	static TArray<UObject*> ParseObjectLibrary(UObjectLibrary* library);
};
