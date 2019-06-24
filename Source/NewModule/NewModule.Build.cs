using UnrealBuildTool;

public class NewModule : ModuleRules
{
	public NewModule(ReadOnlyTargetRules Target):base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {"Core","CoreUObject"});

        //bTreatAsEngineModule = false;
    }
}

