// SPDX-License-Identifier: MPL-2.0

#include "FunctionReferenceCustomization.h"

#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "FunctionReference.h"
#include "IDetailChildrenBuilder.h"
#include "StructUtils/InstancedStruct.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void FBCICoreEditorFunctionReferenceCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Function Reference"))
	];
}

void FBCICoreEditorFunctionReferenceCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TSharedPtr<IPropertyHandle> SubsystemHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBCICoreFunctionReference, Subsystem));
	TSharedPtr<IPropertyHandle> FunctionHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBCICoreFunctionReference, Function));
	TSharedPtr<IPropertyHandle> RequestHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBCICoreFunctionReference, Request));
	
	if (SubsystemHandle.IsValid() && SubsystemHandle->IsValidHandle())
	{
		StructBuilder.AddProperty(SubsystemHandle.ToSharedRef());
		FString ClassPath;
		if (SubsystemHandle->GetValueAsFormattedString(ClassPath) == FPropertyAccess::Success)
		{
			UClass* ResolvedClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *ClassPath));
			if (ResolvedClass)
			{
				TArray<UFunction*> CallableFunctions;

				for (TFieldIterator<UFunction> FuncIt(ResolvedClass, EFieldIteratorFlags::IncludeSuper); FuncIt; ++FuncIt)
				{
					UFunction* Function = *FuncIt;

					if (Function->HasAllFunctionFlags(FUNC_BlueprintCallable) &&
						!Function->HasAnyFunctionFlags(FUNC_Delegate | FUNC_Event)) // optional filters
					{
						CallableFunctions.Add(Function);
					}
				}

				FunctionNames.Empty();

				FString PropertyFunction;
				if (FunctionHandle->GetValueAsFormattedString(PropertyFunction) == FPropertyAccess::Success)
				{
					CurrentSelectedFunction = MakeShared<FString>(PropertyFunction);
					FunctionNames.AddUnique(CurrentSelectedFunction);
				}
				
				for (UFunction* Func : CallableFunctions)
				{
					FString FunctionName = Func->GetName();
					if (!FunctionName.Equals(PropertyFunction))
					{
						FunctionNames.Add(MakeShared<FString>(FunctionName));
					}
				}
				

				if (PropertyFunction.IsEmpty() && FunctionNames.Num() > 0)
				{
					CurrentSelectedFunction = FunctionNames[0];
				}

				StructBuilder.AddCustomRow(FText::FromString("FunctionPicker"))
				.NameContent()
				[
					SNew(STextBlock).Text(FText::FromString("Subsystem Function"))
				]
				.ValueWidget
				[
					SNew(SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&FunctionNames)
					.OnGenerateWidget_Lambda([](TSharedPtr<FString> InItem)
					{
						return SNew(STextBlock).Text(FText::FromString(*InItem));
					})
					.OnSelectionChanged_Lambda([this, FunctionHandle, ResolvedClass, RequestHandle](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
					{
						if (NewSelection.IsValid() && FunctionHandle.IsValid())
						{
							if (FunctionHandle->SetValue(**NewSelection) == FPropertyAccess::Success)
							{
								CurrentSelectedFunction = NewSelection;
								UFunction* Function = ResolvedClass->FindFunctionByName(**CurrentSelectedFunction);
								for (TFieldIterator<FProperty> FuncIt(Function); FuncIt; ++FuncIt)
								{
									if (FStructProperty* StructProperty = CastField<FStructProperty>(*FuncIt))
									{
										UScriptStruct* StructType = StructProperty->Struct;
										FInstancedStruct NewInstanceStruct;
										NewInstanceStruct.InitializeAs(StructType);
										FString ExportedText;
										StructType->ExportText(ExportedText, NewInstanceStruct.GetMemory(), nullptr, nullptr, PPF_None, nullptr);
										ExportedText =  StructType->GetPathName() + ExportedText;
										RequestHandle->SetValueFromFormattedString(ExportedText);
										break;
									}
								}
							}
						}
					})
					.InitiallySelectedItem(CurrentSelectedFunction)
					[
						SNew(STextBlock)
						.Text_Lambda([this]() -> FText
						{
							return CurrentSelectedFunction.IsValid() ? FText::FromString(*CurrentSelectedFunction) : FText::FromString(TEXT("Select Function"));
						})
					]
				];

			}
		}
		StructBuilder.AddProperty(RequestHandle.ToSharedRef());
	}
}
