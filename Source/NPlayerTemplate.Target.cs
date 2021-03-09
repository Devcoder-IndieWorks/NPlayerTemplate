// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NPlayerTemplateTarget : TargetRules
{
	public NPlayerTemplateTarget( TargetInfo Target ) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add( "NPlayerTemplate" );
	}
}
