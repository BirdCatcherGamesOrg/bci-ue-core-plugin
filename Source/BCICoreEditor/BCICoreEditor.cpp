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
	//BCILOG_STARTUP_MODULE(LogBCICoreEditor, FBCICoreEditorModule);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TSharedRef<FBCICoreEditorModule> SharedThis = AsShared();
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FunctionReferenceTypeName,
		FOnGetPropertyTypeCustomizationInstance::CreateSPLambda(SharedThis, [WeakThis = SharedThis->AsWeak()] ()
		{
			TSharedPtr<FBCICoreEditorModule> SharedThis = WeakThis.Pin();
			if (!SharedThis.IsValid())
			{
				BCILOG(LogBCICoreEditor, Error, "Something went wrong with loading the core editor. I'm not as clever as I think I am with smart pointers.");
				checkNoEntry();
			}
				
			if (!SharedThis->Customization.IsValid())
			{
				SharedThis->Customization = MakeShared<FBCICoreEditorFunctionReferenceCustomization>();
			}
				
			return SharedThis->Customization.ToSharedRef();
		})
	);
}

void FBCICoreEditorModule::ShutdownModule()
{
	//BCILOG_SHUTDOWN_MODULE(LogBCICoreEditor, FBCICoreEditorModule);
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(FunctionReferenceTypeName);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBCICoreEditorModule, BCICoreEditor)