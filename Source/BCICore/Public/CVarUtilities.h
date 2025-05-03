// SPDX-License-Identifier: MPL-2.0

#pragma once

#define BCI_CVAR_NAME(X) *(BCICoreCVarUtilities::MakeCVarName(TEXT(UE_MODULE_NAME), TEXT(X)))

struct BCICoreCVarUtilities
{
	
	BCICORE_API static FString MakeCVarName(const FString& CVarName);
	
	BCICORE_API static FString MakeCVarName(const FString& ModuleName, const FString& CVarName);
	
};
