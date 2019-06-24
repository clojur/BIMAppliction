// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BIMAppliction : ModuleRules
{
	public BIMAppliction(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.Add("Runtime/Launch/Public");
        PublicIncludePaths.Add("Runtime/Core/Public");

        PrivateIncludePaths.Add("Runtime/Launch/Private");      // For LaunchEngineLoop.cpp include
        PrivateIncludePaths.Add("Editor/MainFrame/Private");
        PrivateIncludePaths.Add("Runtime/Slate/Public/Framework/Application");
        PrivateDependencyModuleNames.AddRange(
        new string[] {
                "AppFramework",
                "Core",
                "ApplicationCore",
                "Projects",
                "Slate",
                "SlateCore",
                "StandaloneRenderer",
                "SourceCodeAccess",
                "VisualStudioSourceCodeAccess",
        }
    );
    }
}
