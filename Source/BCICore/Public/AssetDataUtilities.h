// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "JsonObjectConverter.h"
#include "Engine/AssetManager.h"

/**
 * Helper for AssetDataUtilities::GetAllAssets which automatically handles GET_MEMBER_NAME_CHECKED.
 */
#define GET_ALL_JSON_ASSETS_CHECKED(ASSETTYPES, CLASSNAME, MEMBERNAME, ASSETS) \
do { \
	AssetDataUtilities::GetAllJSONAssets(ASSETTYPES, GET_MEMBER_NAME_CHECKED(CLASSNAME, MEMBERNAME), ASSETS); \
} while(0)

struct AssetDataUtilities
{
	/**
	 * Get all asset values from possible asset types by a given tag name and deserialize them from JSON strings.
	 */
	template
	<typename T>
	static void GetAllJSONAssets(const TArray<FPrimaryAssetType>& AssetTypes, const FName& Tag, TArray<T>& Assets)
	{
		UAssetManager& AssetManager = UAssetManager::Get();
		for (const FPrimaryAssetType& Type : AssetTypes)
		{
			TArray<FAssetData> AllAssets;
			AssetManager.GetPrimaryAssetDataList(Type, AllAssets);
			for (const FAssetData& Asset : AllAssets)
			{
				T AssetData;
				const bool bDeserialized = FJsonObjectConverter::JsonObjectStringToUStruct(
					Asset.GetTagValueRef<FString>(Tag),
					&AssetData);
				if (bDeserialized)
				{
					Assets.Emplace(AssetData);
				}
				Log(Asset, bDeserialized);
			}
		}
	}

private:
	
	/**
	 * Log the outcome of the operation while hiding the private BCICore log category.
	 */
	BCICORE_API static void Log(const FAssetData& AssetData, bool bDeserialized);
};
