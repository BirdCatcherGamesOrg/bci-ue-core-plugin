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

    TSharedPtr<class IPropertyTypeCustomization> Customization;
};
