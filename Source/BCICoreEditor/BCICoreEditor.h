// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBCICoreEditorModule : public IModuleInterface, public TSharedFromThis<FBCICoreEditorModule>
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:

    template
    <typename T>
    static TSharedRef<class IPropertyTypeCustomization> CreateCustomization();
};

template <typename T>
inline TSharedRef<IPropertyTypeCustomization> FBCICoreEditorModule::CreateCustomization()
{
    return MakeShared<T>();
}
