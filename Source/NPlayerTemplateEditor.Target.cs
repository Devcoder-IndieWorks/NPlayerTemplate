// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NPlayerTemplateEditorTarget : TargetRules
{
	public NPlayerTemplateEditorTarget( TargetInfo Target ) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add( "NPlayerTemplate" );
	}
}
