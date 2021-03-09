// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NPlayerTemplate : ModuleRules
{
	public NPlayerTemplate( ReadOnlyTargetRules Target ) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore", 
                "SlateCore", 
                "Slate", 
                "CinematicCamera"
            }
        );

		PrivateDependencyModuleNames.AddRange( new string[] {} );
	}
}