// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectLibraryParser.h"
#include "Engine.h"

TArray<UObject*> UObjectLibraryParser::ParseObjectLibrary(UObjectLibrary* library)
{
	TArray<UObject*> parsedData;
	
	if(!library) {
		return parsedData;
	}

	TArray<FAssetData> libAssets;
	library->LoadAssetsFromAssetData();

	library->GetAssetDataList(libAssets);
	
	for(FAssetData& asset : libAssets) {
		UObject* obj = asset.GetAsset();
		if(obj) {
			parsedData.Add(obj);
		}
	}

	return parsedData;
}
