// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "UserData.generated.h"

/**
 * @brief FBCICoreUserData is a common struct for versioned data that can be attached to any BCI assets.
 */
USTRUCT(BlueprintType)
struct FBCICoreUserData
{
	GENERATED_BODY()

	/**
	 * @brief UserDataVersion is the version number controlled by the user.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 UserDataVersion = 0;
	
	/**
	 * @brief UserData is arbitrary data encoded as an FString.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserData;
	
};