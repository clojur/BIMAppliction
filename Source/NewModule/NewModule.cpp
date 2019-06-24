
#include "NewModule.h"

DEFINE_LOG_CATEGORY(NewModule);

#define LOCTEXT_NAMESPACE "FNewModule"

void FNewModule::StartupModule()
{
	UE_LOG(NewModule, Warning, TEXT("MyModule has started!"));
}

void FNewModule::ShutdownModule()
{
	UE_LOG(NewModule, Warning, TEXT("MyModule has shut down"));
}

#undef LOCTEXT_NAMESPACE