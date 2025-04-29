// SPDX-License-Identifier: MPL-2.0

#include "BCICoreEditor.h"
#include "BCICoreEditorLogCategory.h"
#include "FunctionReferenceCustomization.h"
#include "BCILog.h"

#define LOCTEXT_NAMESPACE "FBCICoreEditorModule"

namespace
{
	const FName FunctionReferenceTypeName = "BCICoreFunctionReference";
}

void FBCICoreEditorModule::StartupModule()
{
	BCILOG_STARTUP_MODULE(LogBCICoreEditor, FBCICoreEditorModule);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FunctionReferenceTypeName,
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBCICoreEditorModule::CreateCustomization<FBCICoreEditorFunctionReferenceCustomization>)
	);
}

void FBCICoreEditorModule::ShutdownModule()
{
	BCILOG_SHUTDOWN_MODULE(LogBCICoreEditor, FBCICoreEditorModule);
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(FunctionReferenceTypeName);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBCICoreEditorModule, BCICoreEditor)