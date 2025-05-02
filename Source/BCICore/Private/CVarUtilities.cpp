#include "CVarUtilities.h"

FString BCICoreCVarUtilities::MakeCVarName(const FString& CVarName)
{
	return CVAR_NAMESPACE_PREFIX + CVarName;
}

FString BCICoreCVarUtilities::MakeCVarName(const FString& ModuleName, const FString& CVarName)
{
	return CVAR_NAMESPACE_PREFIX + ModuleName + "." + CVarName;
}
