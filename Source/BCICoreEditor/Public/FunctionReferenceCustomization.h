// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "IPropertyTypeCustomization.h"

/**
 * @brief FBCICoreEditorFunctionReferenceCustomization customizes the look of FBCICoreFunctionReference.
 */
struct FBCICoreEditorFunctionReferenceCustomization : IPropertyTypeCustomization
{
    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                 FDetailWidgetRow& HeaderRow,
                                 IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                   IDetailChildrenBuilder& StructBuilder,
                                   IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
                                   
private:
	
   TArray<TSharedPtr<FString>> FunctionNames;
   TSharedPtr<FString> CurrentSelectedFunction;

};
