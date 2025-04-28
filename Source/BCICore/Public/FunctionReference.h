// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "FunctionReference.generated.h"

/**
 * @brief FBCICoreFunctionReference is a customized property which binds a call to a USubsytem's UFUNCTION.
 */
USTRUCT(BlueprintType)
struct FBCICoreFunctionReference
{
	GENERATED_BODY()
	
	/**
	 * @brief Subsystem is the subsystem type to bind to.
	 */
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<class USubsystem> Subsystem;

	/**
	 * @brief Function is the name of the UFUNCTION to call.
	 */
	UPROPERTY(EditAnywhere)
	FName Function;

	/**
	 * @brief Request is an instanced request struct to call the UFUNCTION with.
	 */
	UPROPERTY(EditAnywhere, meta=(StructTypeConst))
	FInstancedStruct Request;
	
};
