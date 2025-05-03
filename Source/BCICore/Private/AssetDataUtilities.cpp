// SPDX-License-Identifier: MPL-2.0

#include "AssetDataUtilities.h"

#include "BCICoreLogCategory.h"
#include "Macros/Log.h"

void AssetDataUtilities::Log(const FAssetData& AssetData, const bool bDeserialized)
{
	if (bDeserialized)
	{
		BCILOG(LogBCICore, Verbose, "Got asset data", {"assetData", AssetData.GetPrimaryAssetId() }, {"deserialized", true });
	}
	else
	{
		BCILOG(LogBCICore, Warning, "Unable to serialize asset", {"assetData", AssetData.GetPrimaryAssetId() }, {"deserialized", false });
	}	
}