// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomEditor.h"

#define LOCTEXT_NAMESPACE "FCustomEditorModule"

void FCustomEditorModule::StartupModule()
{
#if WITH_EDITOR
	AddCustomSection();
#endif
}

void FCustomEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#if WITH_EDITOR
void FCustomEditorModule::AddCustomSection()
{
	#define LOCTEXT_NAMESPACE "Custom Detail"
		static const FName PropertyEditor("PropertyEditor");
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
					
		TSharedRef<FPropertySection> ActorSection = PropertyModule.FindOrCreateSection("Object", "Custom", LOCTEXT("Custom", "Custom"));
		//Categorys that will be available on Custom Section
		ActorSection->AddCategory("Setup");

	#undef LOCTEXT_NAMESPACE
}
#endif

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomEditorModule, CustomEditor)